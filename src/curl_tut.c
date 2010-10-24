#include <stdio.h>
#include <stdlib.h>

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

curl_version_info_data *get_version(void)
{
  curl_version_info_data *version = malloc(sizeof(curl_version_info_data));
  version = curl_version_info(CURLVERSION_NOW);
  printf("CURL version: %s\n", version->version);
  return version;
}

int main(int argc, char **argv)
{
  curl_version_info_data *version;
  CURL *curl;
  CURLcode res;

  char *url;

  if(argc != 2){
    usage();
    return 1;
  }

  url = argv[1];

  initialize();

  curl = curl_easy_init();
  //  curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com/");
  curl_easy_setopt(curl, CURLOPT_URL, url);
  res = curl_easy_perform(curl);

  terminate();

  return 0;
}
