#include <regex.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(void)
{
	    int fd = open("url.html",O_RDWR);
		    off_t size = lseek(fd,0,SEEK_END);//返回文件大小
			    char * mmap_ptr = NULL;
				    //存映射
				
					    mmap_ptr = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
						    //将文件数据映射到进程内存， 通过mmap_ptr可以访问
							    
								    //关于正则代
regex_t reg;
const char*rgx="<a[^>]\\+\\? href=\"\\([^\"]\\+\\?\\)\"[^>]\\+\\?>\\([^<]\\+\\?\\)</a>";
regcomp(&reg,rgx,0);
int reg_num=3;
regmatch_t match[reg_num];
char link[1024];
char target[1024];
while(regexec(&reg,mmap_ptr,reg_num,match,0)==0){
bzero(link,sizeof(link));
bzero(target,sizeof(target));
snprintf(link,match[1].rm_eo-match[1].rm_so,"%s",mmap_ptr+match[1].rm_so);
snprintf(target,match[1].rm_eo-match[1].rm_so,"%s",mmap_ptr+match[1].rm_so);
mmap_ptr+=match[0].rm_eo;

printf(" %s %s\n",link,target);
}




close(fd);
regfree(&reg);

return 0;
}

