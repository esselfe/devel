#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "element.h"

char score_filename[] = "score.dat";

void ScoreLoad(void) {
	FILE *fp;
#ifdef LINUX
	fp = fopen(score_filename, "r");
	if (fp == NULL) {
		printf("ScoreLoad(): Cannot open %s: %s\n", score_filename, strerror(errno));
		return;
	}
#else
	fopen_s(&fp, score_filename, "r");
	if (fp == NULL) {
		char buffer[128];
		strerror_s(buffer, 128, errno);
		printf("ScoreLoad(): Cannot open %s: %s\n", score_filename, buffer);
		return;
	}
#endif
	
	char buffer[64];
	fgets(buffer, 64, fp);
	element_metal_total = (unsigned int)atoi(buffer);
	fgets(buffer, 64, fp);
	element_mineral_total = (unsigned int)atoi(buffer);
	
	fclose(fp);
}

void ScoreSave(void) {
	FILE *fp;
	char buffer[64];
#ifdef LINUX
	fp = fopen(score_filename, "w");
	if (fp == NULL) {
		printf("ScoreSave(): Cannot open %s: %s\n", score_filename, strerror(errno));
		return;
	}
	snprintf(buffer, 64, "%u\n", element_metal_total);
	fputs(buffer, fp);
	snprintf(buffer, 64, "%u\n", element_mineral_total);
	fputs(buffer, fp);
#else
	fopen_s(&fp, score_filename, "w");
	if (fp == NULL) {
		char buffer[128];
		strerror_s(buffer, 128, errno);
		printf("ScoreSave(): Cannot open %s: %s\n", score_filename, buffer);
		return;
	}
	sprintf_s(buffer, 64, "%u\n", element_metal_total);
	fputs(buffer, fp);
	sprintf_s(buffer, 64, "%u\n", element_mineral_total);
	fputs(buffer, fp);
#endif
	fclose(fp);
}
