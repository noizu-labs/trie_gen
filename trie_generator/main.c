

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie_generator.h"

int main(int argc, char *argv[])
{

	char* inputFile = argv[1];
	char defaultOutputFile[] = "import/generated.gen";
	char* outputFile = (argc > 2) ? argv[2] : defaultOutputFile;
	char defaultOutputVar[] = "noizu_trie";
	char* outputVar = (argc > 3) ? argv[3] : defaultOutputFile;
	int structMode = 0;
	int compactMode = 0;


    //---------------------------------
	// Command Line Args
	//---------------------------------
	printf("ARGC = %d, %s\n", argc, argv[0]);
	printf("\n\nARGV2 = %s\n", argv[2]);

	if (argc < 2) {
		printf("Usage: trie_generator.exe input.txt [output.file|import/generated.gen] [name|trie] [mode|(min|struct|compact)]");
		return 1;
	}
	
	if (argc > 4) {
		structMode = (strncmp(argv[4], "struct", 6) == 0) ? 1 : 0;
		compactMode = (strncmp(argv[4], "compact", 6) == 0) ? 1 : 0;
	}
	

	//---------------------------------
	// Runtime Settings
	//---------------------------------
	printf("------------------[Noizu Trie Gen: %d]---------------------\n", argc);
	printf("Input File: %s\n", inputFile);
	printf("Output File: %s\n", outputFile);
	printf("Output Name: %s\n", outputVar);
	printf("Trie Type: %s\n", structMode ? "NoizuStaticTrie" : (compactMode ? "NoizuCompactTrie" : "NoizuMicroTrie"));
	printf("-------------------------------------------------------\n");

	//---------------------------------
	// Load Trie
	//---------------------------------
	NoizuAutoTrie* root = (NoizuAutoTrie*)malloc(sizeof(NoizuAutoTrie));
	if (root) {
		memset(root, 0, sizeof(NoizuAutoTrie));
		root->key = '*';
	}
	else {
		printf("[Error] Malloc Fail Line:%d", __LINE__);
		return 1;
	}

	FILE *fptr;
	errno_t err;
	err = fopen_s(&fptr, inputFile, "r");
	if (!err && fptr) {		
		char line[2048] = { 0 };
		int pos = 0;
		// grab line, since getline isn't handy on windows. 
		char c = 0;
		while (TRUE) {
			pos = 0;
			while ((c = fgetc(fptr)) != EOF) {
				line[pos] = c;
				if (c == '\n' || c == '\r') {
					break;
				}
				pos++;
			}
			line[pos] = '\0';
			//printf("Line: %s\n", line);
			char token[256] = { 0 };
			char code[256] = { 0 };

			if (sscanf_s(line, "#! GENERATE `%[^|\n\r`]`", token, 255) == 1) {
				outputVar = malloc(strlen(token) + 1);
				if (outputVar) {
					strncpy_s(outputVar, strlen(token) + 1, token, 255);
				}				
			} else if (strncmp(line, "#", 1) == 0) {
				// Comment
			}
			else if (sscanf_s(line, "%[^|\n\r ]|%[^\n\r]", code, 255, token, 255) == 2) {
				insert(token, code, root);
			}
			if (c == EOF) break;			
		}


		//---------------------------------
		// Output Trie
		//---------------------------------
		
		err = fopen_s(&fptr, outputFile, "w");
		if (!err && fptr) {
			

			if (compactMode) {
				gen_prep_depth_first(root);
				noizu_auto_trie_compact_details* details = (noizu_auto_trie_compact_details*)malloc(sizeof(noizu_auto_trie_compact_details));
				if (details) {
					memset(details, 0, sizeof(noizu_auto_trie_compact_details));
				}
				else {
					printf("[Error] Malloc Fail Line:%d", __LINE__);
					return 1;
				}

				// calculate compact implementation details. 
				gen_prep_details(root, details);
				gen_compact_format(outputVar, root, details, fptr);

			} else if (structMode) {
				gen_prep(root);
				gen_struct_format(outputVar, root, fptr);
			}
			else {
				gen_prep(root);
				gen_array_format(outputVar, root, fptr);
			}
			fclose(fptr);
			printf("\n\n[Complete: %s]\n\n\n", outputFile);
			return 0;
		}
		else {
			printf("\n\n[Error] - Openning Output File %s", outputFile);
			return 2;
		}
	}
	else {
		printf("\n\n[Error] - Opening Input File %s", inputFile);
		return 3;
	}
}