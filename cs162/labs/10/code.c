int main(){
	char str[100], ans; 
	int i=0; 
 
	while((ans=getchar())!='\n') 
 		str[i++]=ans; 
	str[i]='\0'; 
	printf("%s\n", str);
}