#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>

#include <curl/curl.h>

int initialize(void)
{
  curl_global_init(CURL_GLOBAL_SSL);
  return 0;
}

int terminate(void)
{
  curl_global_cleanup();
}

int usage(void)
{
    printf("usage: curl_tut [url]\n");
    return 0;
}

int main(int argc, char **argv)
{
  curl_version_info_data *curlinfo;
  CURL *curl;
  CURLcode res;
  FILE *fp;
  int ch;
  extern char *optarg;
  extern int optind, opterr;
  char filename[256] = "";

  char *url;


  while ((ch = getopt(argc, argv, "o:")) != -1){
    switch (ch){
    case 'o':
      strncpy(filename,optarg,256);
      break;
    default:
      usage();
      return 1;
    }
  }
  argc -= optind;
  argv += optind;

  if(argc != 1){
    fprintf(stderr, "argc:%d\n", argc);
    usage();
    return 1;
  }else{
    url = argv[0];
  }

  if (strlen(filename) != 0) {
    if ((fp = fopen(filename, "w")) == NULL){
      fprintf(stderr,"error:failed to open file\n");
      return errno;
    }
  } else {
    fp = stdout;
  }


  initialize();

  curl = curl_easy_init();
  if(!curl){
    fprintf(stderr,"error:initialize failed\n");
    return CURLE_FAILED_INIT;
  }

  curlinfo = curl_version_info(CURLVERSION_NOW);

  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
  curl_easy_setopt(curl, CURLOPT_URL, url);
  res = curl_easy_perform(curl);

  terminate();
  fclose(fp);

  return 0;
}
