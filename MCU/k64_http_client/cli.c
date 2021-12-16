/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#include "cli.h"

#include "lwip/opt.h"

#include "lwip/sys.h"
#include "lwip/api.h"

#include <lwip/sockets.h>
#include "lwipopts.h"  
#include "fsl_debug_console.h"

#define PORT            80
#define IP_ADDR        "114.215.151.106"

#ifdef    LWIP_DNS
#define   HOST_NAME       "api.seniverse.com"     //www.lighttpd.net"

#else
#define   HOST_NAME       "114.215.151.106"     //
#endif

uint8_t get_buf[]= "GET /v3/weather/now.json?key=hz7l61itggsqc2ex&amp&location=beijing&amp&language=zh-Hans&amp&unit=c HTTP/1.1\r\nHost: api.seniverse.com\r\n\r\n\r\n\r\n";

#define BUF_LEN  4096

static void client(void *thread_param)
{
  int sock = -1,rece;
  struct sockaddr_in client_addr;
  
  char* host_ip;
  
  uint32_t *pSDRAM= pvPortMalloc(BUF_LEN);
  
#ifdef  LWIP_DNS
    ip4_addr_t dns_ip;
    netconn_gethostbyname(HOST_NAME, &dns_ip);
    host_ip = ip_ntoa(&dns_ip);
    PRINTF("host name : %s , host_ip : %s\n",HOST_NAME,host_ip);
#else
    host_ip = HOST_NAME;
#endif  
  
  while(1)
  {
		/*��������*/
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
      PRINTF("Socket error\n");
      vTaskDelay(10);
      continue;
    } 
    client_addr.sin_family = AF_INET;      
    client_addr.sin_port = htons(PORT);   
    client_addr.sin_addr.s_addr = inet_addr(host_ip);
    memset(&(client_addr.sin_zero), 0, sizeof(client_addr.sin_zero)); 
		
		/*���ӵ�����������*/
    if (connect(sock, 
               (struct sockaddr *)&client_addr, 
                sizeof(struct sockaddr)) == -1)
    {
        PRINTF("Connect failed!\n");
        closesocket(sock);
        vTaskDelay(10);
        continue;
    }                                           
    
    PRINTF("Connect to server successful!\n");
		memset(pSDRAM,0,BUF_LEN);
    PRINTF("\n************************************************************\n");
		/*����http������*/
    write(sock,get_buf,sizeof(get_buf));
    while (1)
    {
			//�ȴ��������˵�Ӧ�𣬲��ҽ�������
      rece = recv(sock, (uint8_t*)pSDRAM, BUF_LEN, 0);
      if (rece <= 0) 
        break;

      PRINTF("%s\n",(uint8_t*)pSDRAM);

    }
    PRINTF("\n**********************************************************\n");
    
    memset(pSDRAM,0,BUF_LEN);
    closesocket(sock);
    vTaskDelay(10000);
  }
}

void
client_init(void)
{
  sys_thread_new("client", client, NULL, 2048, 4);
}
