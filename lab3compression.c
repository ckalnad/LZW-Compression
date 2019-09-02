#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc,char *argv[])
{
		int j=0,mm=0,m=0,n,len=0,ii=0;
		unsigned char Cfpt;
		unsigned int *data_len=(unsigned int *)calloc(65536,sizeof (int));
		
		unsigned short int compcode=0;
		unsigned char **data=(unsigned char **)calloc(65536,sizeof(unsigned char *));

		//Allocate memory
		for(j=0;j<65536;j++)
		{
				data[j]=(unsigned char *)calloc(100,sizeof(unsigned char *));
		}

		FILE *fpt1, *fpt2;
		fpt1 = fopen(argv[1],"rb");
		fpt2 = fopen("comp.lzw","wb");

		//Initializing data and data_len
		for(mm=0;mm<256;mm++)
		{
				data_len[mm]=1;
				data[mm][0]=mm;

		}

		rewind(fpt1);//Resetting pointer

		len = 0;


		unsigned char *PP=(unsigned char *)calloc(100,sizeof(unsigned char *));
		unsigned char *QQ=(unsigned char *)calloc(100,sizeof(unsigned char *));
		unsigned char *RR=(unsigned char *)calloc(100,sizeof(unsigned char *));


		while (fread(&Cfpt,1,1,fpt1) > 0)
		{
			
			for(ii=0;ii<len;ii++)
			{
				QQ[ii]=PP[ii];
				RR[ii]=PP[ii];
			}
			//printf("%d\n",len);

			PP[len]=Cfpt;
			len++;

			for(n=0;n<mm;n++)
			{
				
				if (data_len[n] == len)
				{
					if(memcmp(PP,data[n],len)==0)
					{
						m=1;
						compcode=(short int)n;
						break;
					}
				}
			}

				
			if(m == 1)
			{
				m=0;

				continue;
			}

			else
			{
				len--;

				for(n=0; n<mm; n++)
				{
					if (data_len[n] == len)
					{
						if(memcmp(QQ, data[n], len) == 0)
						{
							compcode = (short int)n;
							break;
						}
					}
				}

				fwrite(&compcode,2,1,fpt2);

				for(ii=0;ii<len+1;ii++)
				{
					data[mm][ii]=PP[ii];
				}

				data_len[mm] = len + 1;
				mm++;
				
				len=1;
				PP[0]=Cfpt;
			}
		}
		
	
	for(n=0;n<mm;n++)
	{
		if(memcmp(PP,data[n],len) == 0)
		{
			compcode=(short int)n;
			break;
		}
	}

	fwrite(&compcode,2,1,fpt2);
	fclose(fpt1);
	fclose(fpt2);
}