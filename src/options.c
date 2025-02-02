#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include <errno.h>

#include "ts.h"


#define OPT_HELP 		"help"
#define OPT_FORMAT		"format"
#define OPT_BRIEF_LIST	"brief"
#define OPT_DETAIL_LIST	"details"
#define OPT_VERSION		"version"
#define OPT_MEMORY		"mem"
#define OPT_TABLE		"table"

enum {
	/* long options mapped to a short option */
	OPT_HELP_NUM         = 'h',
	OPT_FORMAT_NUM       = 'f',
	OPT_BRIEF_LIST_NUM   = 'b',
	OPT_DETAIL_LIST_NUM  = 'd',
	OPT_VERSION_NUM      = 'v',
	OPT_MEMORY_NUM       = 'm',
	OPT_TABLE_NUM        = 's',
};

static struct tsa_config tsaconf = {
	.brief = 1,
};

struct tsa_config *get_config()
{
	return &tsaconf;
}

int check_filepath_valid(char *filename)
{
	if(filename==NULL)
		return -1;
	int fd = open(filename,O_RDONLY);
	if(fd<0)
		return -1;
	close(fd);
	return 0;
}

int parse_table(const char *table)
{
#define TABLE_NUM (9)
	const char* tables[TABLE_NUM]={"pat","cat","pmt","tsdt",
		"nit","sdt","bat","tdt","tot"};
	int i = 0;
	for(i=0; i<TABLE_NUM; i++)
	{
		if(strcmp(table,tables[i])==0)
		{
			tsaconf.tables = i;
			return 0;
		}
	}
	return -1;
}

int parse_format_type(const char *format)
{
#define FORMAT_NUM (2)
	int i = 0;
	const char* formats[FORMAT_NUM]={
		"file","udp"
	};
	for(i=0; i<FORMAT_NUM; i++)
	{
		if(strcmp(formats[i],format)==0)
		{
			return i;
		}
	}
	return -1;
}

void prog_usage(FILE *fp,const char* pro_name)
{
	if(fp == NULL)
		fp = stderr;
	fprintf(fp,"Usage: %s [optins]... <file>\n", pro_name);
	fprintf(fp,"  Display infomations about mpeg ts.\n\n");
	fprintf(fp,"%13s%c%s\t%s\n","  -",OPT_HELP_NUM,", --"OPT_HELP,"Show this help");
	fprintf(fp,"%13s%c%s\t%s\n","  -",OPT_FORMAT_NUM,", --"OPT_FORMAT,"Select input file or net io format");
	fprintf(fp,"%13s%c%s\t%s\n","  -",OPT_BRIEF_LIST_NUM,", --"OPT_BRIEF_LIST,"Show all infos in brief");
	fprintf(fp,"%13s%c%s\t%s\n","  -",OPT_DETAIL_LIST_NUM,", --"OPT_DETAIL_LIST,"Show all infos in detail");
	fprintf(fp,"%13s%c%s\t%s\n","  -",OPT_VERSION_NUM,", --"OPT_VERSION,"Show version");
	fprintf(fp,"%13s%c%s\t%s\n","  -",OPT_MEMORY_NUM,", --"OPT_MEMORY,"memory to use");
	fprintf(fp,"%13s%c%s\t%s\n","  -",OPT_TABLE_NUM,", --"OPT_TABLE,"Show select tables only");
	fprintf(fp,"\n\n");
}

int prog_parse_args(int argc, char **argv)
{
	int opt,ret;
	int option_index;
	const char *prgname = argv[0];

	//make a copy of the options
	const char short_options[]=
		"b" 	/* brief */
		"d" 	/* details */
		"h" 	/* help */
		"m:" 	/* memory size */
		"v" 	/* version */
		"s:"	/* tables */
		"f:"	/*format*/
	;

	const struct option long_options[]={
			{OPT_BRIEF_LIST, 1, NULL, OPT_BRIEF_LIST_NUM},
			{OPT_DETAIL_LIST, 0, NULL, OPT_DETAIL_LIST_NUM },
			{OPT_VERSION, 0, NULL, OPT_VERSION_NUM },
			{OPT_HELP, 0, NULL, OPT_HELP_NUM },
			{OPT_MEMORY, 1, NULL, OPT_MEMORY_NUM},
			{OPT_TABLE, 0, NULL, OPT_TABLE_NUM },
			{OPT_FORMAT, 1, NULL, OPT_FORMAT_NUM},
			{0, 0, NULL, 0 }
		};

	if(argc < 2)
	{
		prog_usage(stdout,prgname);
		return -EINVAL;
	}

	while((opt = getopt_long(argc,argv,short_options,
		long_options,&option_index)) != EOF){
		if(opt == '?'){
			prog_usage(stdout,prgname);
			return -EINVAL;
		}
		//printf("parse %c %s\n",opt,optarg);
		switch(opt){
		case 'h':
			prog_usage(stdout,prgname);
			exit(0);
		case 'b':
			tsaconf.brief = 1;
			break;
		case 'd':
			tsaconf.detail = 1;
			break;
		case 's':
			tsaconf.tables = parse_table(optarg);
			break;
		case 'f':
			tsaconf.type = parse_format_type(optarg);
			break;
		case 'v':
			printf("version 1.0.0rc.\n");
			break;
		default:
			break;
		}
	}

	strncpy(tsaconf.name,argv[argc-1],256);

	if(tsaconf.type==UINT8_MAX)
		return -EINVAL;
	if(tsaconf.type == 0)
	{
		if(check_filepath_valid(argv[argc-1])<0)
		{
			printf("no such file or invalid filepath\n");
			return -ENOENT;
		}
	}

	return 0;
}

