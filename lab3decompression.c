#include <stdio.h>
#include <stdlib.h>
#include <string.h>



 int main(int argc,char *argv[])
{
	

	FILE *fpt1,*fpt2;
	
	fpt1=fopen("comp.lzw","rb");
	fpt2=fopen("decomp.lzw","wb");


	int j=0,mm=0,length=0;
	unsigned char B,C;
	unsigned int *data_len=(unsigned int *)calloc(65536,sizeof (int));
	
	
	unsigned char *Z=(unsigned char *)malloc(21);
	unsigned short int QQ=0,WW=0;
	unsigned short int *decomcode=(unsigned short int *)calloc(65536,sizeof(unsigned char *));;
	unsigned char **datade=(unsigned char **)calloc(65536,sizeof(unsigned char *));

	
	for(j=0;j<65536;j++)
	{
		datade[j]=(unsigned char *)calloc(100,sizeof(unsigned char *));
		
	}

	

	if((j=fgetc(fpt1))==-1)
	{
		exit(0);
	}
	
	//Initializing Dictionary
	for(mm=0;mm<256;mm++)
	{
		data_len[mm]=1;
		datade[mm][0]=mm;
	}


	rewind(fpt1);
	fread(decomcode,1,2,fpt1);
	
	QQ=(short int)decomcode[0];

	fwrite(datade[QQ],1,data_len[QQ],fpt2);
	
	WW=QQ;
	
	
	
	unsigned char *temp1=(unsigned char *)calloc(100,sizeof(unsigned char *));
	unsigned char *temp3=(unsigned char *)calloc(100,sizeof(unsigned char *));


	int uu=0;

	while(fread(decomcode,1,2,fpt1)>0)
	{
		
		QQ=decomcode[0];
		if(QQ<mm || QQ<256)
		{
			fwrite(datade[QQ],1,data_len[QQ],fpt2);
			for(uu=0;uu<data_len[WW];uu++)
			{
				temp1[uu]=datade[WW][uu];
			}
			
			temp3[0]=datade[QQ][0];
			
			
			length=data_len[WW]+1;
			
			for(uu=0;uu<data_len[WW];uu++)
			{
				datade[mm][uu]=datade[WW][uu];
			}
			
			datade[mm][uu]=temp3[0];
			
			data_len[mm]=length;
			
			mm++;
		}
		
		else
		{
			for(uu=0;uu<data_len[WW];uu++)
			{
				temp1[uu]=datade[WW][uu];
			}
			
			Z[0]=datade[WW][0];
			
			length=data_len[WW]+1;
			
			fwrite(datade[WW],1,data_len[WW],fpt2);
			
			fwrite(datade[WW],1,1,fpt2);
			
			for(uu=0;uu<data_len[WW];uu++)
			{
				datade[mm][uu]=datade[WW][uu];
			}
			datade[mm][uu]=Z[0];
			
			data_len[mm]=length;
			
			mm++;
		}
		WW=QQ;
	}
	fclose(fpt1);
	fclose(fpt2);
}

