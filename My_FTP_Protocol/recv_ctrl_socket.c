/*
 * recv_ctrl_socket.c
 *
 *  Created on: 2015-05-24
 *      Author: sajjad
 */

#include <recv_ctrl_socket.h>

char recv_response(int sockfd) {
	//Receiving msg response
	char buffer[128];
	memset(&buffer,0,128);
	char chbuffer[2];
	memset(&chbuffer,0,2);
	char status=0;

	char message_flag=1;
	while (message_flag){
		memset(&buffer,0,128);

		char line_flag=1;
		while (line_flag) {
			memset(&chbuffer,0,2);
			status = recv(sockfd, (void *)chbuffer,1,0);
			if (status==0) {
				printf ("Connection terminated.\n");
				message_flag=0;
				line_flag=0;
			}
			if (status==-1){
				perror("Error: Reading RESPONSE failed\n");
				return -1;
			}
			strcat(buffer,chbuffer);
			if ('\n'==chbuffer[0]) {
				line_flag=0;

			}
		}
		printf("%s", buffer);
		if (' '==buffer[3]) {
			message_flag=0;
		}
	}
	char temp[4]={0};
	strncpy(temp,buffer,3);
	if (strstr(temp,"227")) {
		char tIP[16]={0};
		int data_port=0;
		recv_pd_info(buffer,tIP,data_port);
	}
	printf ("server message fully received.\n");
	return 0;
}

