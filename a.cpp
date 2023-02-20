/*!
 *    \file  a.c
 *   \brief  
 *
 *  <+DETAILED+>
 *
 *  \author  KIM Hyeok (kh), ekh0324@gmail.com
 *
 *  \internal
 *       Created:  2019년 03월 18일
 *      Revision:  none
 *      Compiler:  gcc
 *  Organization:  Konkuk University
 *     Copyright:  Copyright (c) 2019, KIM Hyeok
 *
 *  This source code is released for free distribution under the terms of the
 *  GNU General Public License as published by the Free Software Foundation.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <error.h>

#include <fstream>
#include<locale.h>
#include <iconv.h>
#define BLUE(string) "\x1b[34m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"
using namespace std;

extern char* _libc_intl_domainname;
extern int errno;
int main() {

	char offset_name[100][100] ;
	char magic_name[100][30] = {
"매직애로우",
"블래스트",
"썬더",
"파이어볼",
"메테오",
"블리자드",
"토네이도",
"턴언데드",
"어스퀘이크",
"힐1",
"힐2",
"포스힐1",
"포스힐2",
"슬립",
"뮤트",
"프로텍션1",
"프로텍션2",
"어택1",
"어택2",
"존",
"텔레포트",
"레지스트",
"참",
"퀵",
"어게인",
"디클레인",
"발키리",
"프레이어",
"화이트드래곤",
"사라만다",
"아이언골렘",
"데몬로드",
	};
	char wingbonus_name[100][20]= {"불가", "가능"};
	char classtype_name[100][20] = {
		"보병","승병","창병","기마","마족기마","비병","도적","수병",
		"겔","마족","마족수병","레인저","법사","유령","불사","궁병","발리스타","용족"
	};
	string class_name[500] ;
	for(int j=0; j<100; j++) {
		sprintf(offset_name[j], BLUE("%d"), j);
	}
	
	sprintf(offset_name[0x01], "%s", "FLY");
	sprintf(offset_name[0x02], "%s", "CLASSTYPE");
	sprintf(offset_name[0x03], "%s", "TIER");
	sprintf(offset_name[0x04], "%s", "AT");
	sprintf(offset_name[0x05], "%s", "DF");
	sprintf(offset_name[0x06], "%s", "MV");
	sprintf(offset_name[0x07], "%s", "CS");
	sprintf(offset_name[0x08], "%s", "A");
	sprintf(offset_name[0x09], "%s", "D");
	sprintf(offset_name[0x0a], "%s", "MP");
	sprintf(offset_name[0x0b], "%s", "MD");
	sprintf(offset_name[0x12], "%s", "용병1");
	sprintf(offset_name[0x14], "%s", "용병2");
	sprintf(offset_name[0x16], "%s", "용병3");


	ifstream if_classname("CLASSNAME.txt");
	int i_classid=0;
	while( getline(if_classname,class_name[i_classid])) {
		i_classid++;
	}

	int8_t buf[100];

	FILE * input = fopen("CLASS.DAT", "rb");
//	int input = open("magic1.dat", O_RDONLY);
  
//	ifstream reader;
//	reader.open("magic1.dat", ios::binary);

	int uid = 0;

	size_t result;
	while(feof(input) ==0) {

		fread( buf, 1,28, input);



		printf("id:%d, %s\n",uid , class_name[uid].c_str()); 

		for (int i=0; i <28; i=i+1) {
			uint8_t* data2;
			if( i%4 ==0)
				putchar('\n');
			else putchar('\t');
			switch(i){
				case 0x1:
					data2 = (uint8_t*)&buf[i];
					if(*data2 == 1)
						printf("%s,", offset_name[i]);
					break;
				case 0x2:
					data2 = (uint8_t*)&buf[i];
					printf("%s,",  classtype_name[*data2]);
					break;
				case 18: case 20: case 22:
					data2 = (uint8_t*)&buf[i];
					if (*data2 == 0) continue;
					printf("%s%s,", offset_name[i], class_name[*data2].c_str());
					break;
				case 24: case 25: case 26: case 27:
					data2 = (uint8_t*)&buf[i];
					if (*data2 == 255) continue;
					printf("%s%s,", offset_name[i], magic_name[( *data2 )]);
					break;
				case 12:
					data2 = (uint8_t*)&buf[i];
					printf("%s%+d", "용병수정치:",(*data2));
					break;
				case 13:
					data2 = (uint8_t*)&buf[i];
					printf("%s%d원", "가격:",(*data2)*10);
					break;
				case 0: case 19: case 21: case 23:
			break;
				default:
					data2 = (uint8_t*)&buf[i];
					printf("%s%+3d,", offset_name[i],( *data2 ));
					break;
			}
		}


		puts("\n");
		uid++;

	}

}
