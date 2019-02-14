#include <stdio.h>

void reverse_line(char line[], int line_lenght){
	
	int i;
	char temporary;
	for(i=0;i<line_lenght/2;i++){		//array boyutunun yarisi kadar doner ve bastaki elemani once gecici degiskene sonra array 
		temporary=line[i];		//sonuna atar bu islem array boyutunun yarisina kadar devam eder. 
		line[i]=line[line_lenght-1-i];
		line[line_lenght-1-i]=temporary;
	}
}
int find_size_of_line(char line[]){
	int i,size;
	size=0;
	for(i=0;line[i]!='\0';i++)		//NULL karakter olmadigi sürece döngü devam eder ve size bulunur.
		size=size+1;
	return size;
}
void encrypt_open_msg(){
	
	int key,i;
	char line[1025];

	FILE *fpr,*fpw;
	
	printf("Enter a number between 1 and 26 for Key: "); //kullanicidan sifrelemede kullanilacak aralik istenir
	scanf("%d",&key);
	
	fpr=fopen("open_msg.txt","r");  //okumak icin acilan dosya
	fpw=fopen("secret_msg.txt","w");//yazmak icin acilan dosya
	
	while(fgets(line,1025,fpr)!=NULL){ //dosya sonuna gelmedikce veya okumada bir sorun cikmadigi sürece satiri okumayi saglar
	if(line[find_size_of_line(line)-1]=='\n'){//eger satir sonunda yeni satır karakteri var ise terse döndürmeyi sifrelemeyi 
		reverse_line(line,find_size_of_line(line)-1);//bu karaktere kadar yapar.
		for(i=0;i<find_size_of_line(line)-1;i++){
			if(line[i]==' ')
				line[i]='_';
			else if(line[i]=='.')
				line[i]='*';
			else{
				if(line[i]-key<97){  //eger key kadar önceki harf kendisinden sonra geliyorsa
					line[i]='z'-(+97+key-line[i]-1);}
				else
					line[i]=line[i]-key;//eger key kadar onceki harf kendisinden once geliyorsa
			}
		}
		fprintf(fpw,"%s",line);
	}
	else{				//satir sonunda yeni satir elemani yoksa
		reverse_line(line,find_size_of_line(line));
		for(i=0;i<find_size_of_line(line);i++){
			if(line[i]==' ')
				line[i]='_';
			else if(line[i]=='.')
				line[i]='*';
			else{
				if(line[i]-key<97)
					line[i]='z'-(+97+key-line[i]-1);
				else
					line[i]=line[i]-key;
			}
		}
	fprintf(fpw,"%s",line); //ters cevirip sifreledigimiz satir dosyaya yazariz
	}
	printf("%s",line);    //bu satiri ekranda bastiririz
	}
	fclose(fpr);
	fclose(fpw);
}
void decrypt_secret_msg(){
	
	int key,i;
	char line[1025];

	FILE *fpr,*fpw;
	
	printf("Enter a number between 1 and 26 for Key: ");
	scanf("%d",&key);
	
	fpr=fopen("secret_msg.txt","r");
	fpw=fopen("open_msg.txt","w");
	
	while(fgets(line,1025,fpr)!=NULL){
	if(line[find_size_of_line(line)-1]=='\n'){ //satir sonunda eger yeni yeni satır karatkteri yoksa
		reverse_line(line,find_size_of_line(line)-1);
		for(i=0;i<find_size_of_line(line)-1;i++){
			if(line[i]=='_')
				line[i]=' ';
			else if(line[i]=='*')
				line[i]='.';
			else{
				if(line[i]+key>122){ //eger key kadar sonraki harf kendisinden önce ise
					line[i]='a'+(-122+key+line[i]-1);}
				else
					line[i]=line[i]+key;//eger key kadar sonraki harf kendisinden sonra ise
			}
		}
		fprintf(fpw,"%s",line);
	}
	else{				//eger satir sonunda yeni satir elemani yoksa
		reverse_line(line,find_size_of_line(line));
		for(i=0;i<find_size_of_line(line);i++){
			if(line[i]=='_')
				line[i]=' ';
			else if(line[i]=='*')
				line[i]='.';
			else{
				if(line[i]-key>122)
					line[i]='a'+(122+key-line[i]-1);
				else
					line[i]=line[i]+key;
			}
		}
	fprintf(fpw,"%s",line); //sifresi cözülen satir yazmak icin acilan dosyaya yazilir
	}
	printf("%s",line);//sifresi cözülen satir ekrana basilir
	}
	fclose(fpr);
	fclose(fpw);
}
void menu(){

	int user_choice;

	do{
		printf("1. Encrypt\n");
		printf("2. Decrypt\n");
		printf("0. Exit\nChoice:");
		scanf("%d",&user_choice);
		switch(user_choice){
		
			case 1:
				encrypt_open_msg();
				break;
			case 2:
				decrypt_secret_msg();
				break;
			default:
				break;}
	}while(user_choice!=0);
}
int main(){
	menu();
	return 0;
}
		

















