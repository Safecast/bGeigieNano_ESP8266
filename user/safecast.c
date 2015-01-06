#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"
#include "uart.h"

#include "c_types.h"
#include "espconn.h"
#include "mem.h"
#include "safecast.h"
#include "debug.h"
#include "nsscanf.h"

char json[1024];

static void ICACHE_FLASH_ATTR safecast_lookup_complete_cb(const char *name, ip_addr_t *ip, void *arg) {
  static esp_tcp tcp;
  struct espconn *conn=(struct espconn *)arg;
  if (ip==NULL) {
    debug("DNS lookup failed\n");
    network_init();
  }

  debug("DNS lookup successful");

  char page_buffer[40];
  os_sprintf(page_buffer,"IP: %d.%d.%d.%d\n", *((uint8 *)&ip->addr), *((uint8 *)&ip->addr + 1), *((uint8 *)&ip->addr + 2), *((uint8 *)&ip->addr + 3));
  debug(page_buffer);

  conn->type=ESPCONN_TCP;
  conn->state=ESPCONN_NONE;
  conn->proto.tcp=&tcp;
  conn->proto.tcp->local_port=espconn_port();
  conn->proto.tcp->remote_port=80;
  os_memcpy(conn->proto.tcp->remote_ip, &ip->addr, 4);
  espconn_regist_connectcb(conn, safecast_connected_cb);
  espconn_regist_disconcb(conn, safecast_disconnected_cb);
  espconn_regist_reconcb(conn, safecast_reconnected_cb);
  espconn_regist_recvcb(conn, safecast_recv_cb);
  espconn_regist_sentcb(conn, safecast_sent_cb);
  espconn_connect(conn);
}

static void ICACHE_FLASH_ATTR safecast_sent_cb(void *arg) {
  debug("sent");
}

static void ICACHE_FLASH_ATTR safecast_recv_cb(void *arg, char *data, unsigned short len) {

  debug("recv");
  
  struct espconn *conn=(struct espconn *)arg;
  int x;
  uart0_tx_buffer(data,len);
}

static void ICACHE_FLASH_ATTR safecast_connected_cb(void *arg) {

  uart0_tx_buffer("conn",4);
  struct espconn *conn=(struct espconn *)arg;

  char transmission[1024];

  char *header = "POST /measurements.json?api_key=YOURAPIKEY HTTP/1.1\r\n"
                 "Host: dev.safecast.org\r\n"
                 "Accept: */*\r\n"
                 "User-Agent: Arduino\r\n"
                 "Content-Type: application/json\r\n"
                 "Content-Length: ";
 
 
  int head_len = strlen(header);
  int json_len = strlen(json);

  char json_len_str[10];
  os_sprintf(json_len_str,"%d",json_len);
  int json_len_str_len = strlen(json_len_str);

  strcpy(transmission,header);
  strcpy(transmission+head_len,json_len_str);
  strcpy(transmission+head_len+json_len_str_len,"\r\n\r\n");
  strcpy(transmission+head_len+json_len_str_len+4,json);

  sint8 d = espconn_sent(conn,transmission,strlen(transmission));

  espconn_regist_recvcb(conn, safecast_recv_cb);
  uart0_tx_buffer("cend",4);
}

static void ICACHE_FLASH_ATTR safecast_reconnected_cb(void *arg, sint8 err) {
  uart0_tx_buffer("rcon",4);
}

static void ICACHE_FLASH_ATTR safecast_disconnected_cb(void *arg) {
  uart0_tx_buffer("dcon",4);
}


void ICACHE_FLASH_ATTR safecast_send_data() {
  static struct espconn conn;
  static ip_addr_t ip;

  debug("network lookup\n");
  espconn_gethostbyname(&conn, "dev.safecast.org", &ip, safecast_lookup_complete_cb);
}



void ICACHE_FLASH_ATTR safecast_send_nema(char *nema_string) {

  int valid = safecast_nema2json(nema_string,json);

  // normal we will only want to send valid data...
  safecast_send_data();
}

// json_string needs to be preallocated and large enough to hold the output
// Convert NEMA e.g.:
//$BNRDD,[4digit_device_id],[ISO8601_time],[cpm],[cpb],[total_count],[geiger_status],[lat],[NS],[long],[WE],[altitude],[gps_status],[nbsat],[precision]
// To JSON e.g. (but I've added captured_at):
//{"longitude":"111.1111","latitude":"11.1111","device_id":"47","value":"63","unit":"cpm"}
static ICACHE_FLASH_ATTR int safecast_nema2json(const char *nema_string,char *json_string) {

  int    device_id;
  char   iso_timestr[50];
  int    cpm;
  int    cpb;
  int    total_count;
  char   geiger_status;
  double latitude;
  char   NorS;
  double longitude;
  char   WorE;
  double altitude;
  char   gps_status;
  int    nbsat;
  int    precision;

  nsscanf(nema_string,
         "$BNRDD,%04d,%[^,],%d,%d,%d,%c,%f,%c,%f,%c,%f,%c,%d,%d",
         &device_id,
         iso_timestr,
         &cpm,
         &cpb,
         &total_count,
         &geiger_status,
         &latitude,
         &NorS,
         &longitude,
         &WorE,
         &altitude,
         &gps_status,
         &nbsat,
         &precision);

  if(NorS == 'S') latitude  = 0-latitude;
  if(WorE == 'W') longitude = 0-longitude;

  os_sprintf(json_string,"{captured_at\":\"%s\",\"device_id\",\"%d\",\"value\":\"%d\",\"unit\":\"cpm\"}", iso_timestr, longitude, latitude, device_id, cpm);

  if((gps_status == 'A') && (geiger_status == 'A')) return 1;
                                               else return 0;

}
