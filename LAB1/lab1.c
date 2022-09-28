#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//PRES son palabras reservadas en mayuscula para generar la salida
//pres son palabras reservadas en minuscula para realizar comparaciones
//sres son simbolos reservados para realizar comparaciones y generar la salida
char PRES[30][10]={"PROGRAM","CONST","TYPE","VAR","INTEGER","REAL","BOOLEAN","PROCEDURE","FORWARD","FUNCTION","BEGIN","END","IF","THEN","ELSE","CASE","OF","WHILE","DO","FOR","TO","DOWNTO","REPEAT","UNTIL","OR","DIV","MOD","AND","NOT","CHAR"};
char pres[30][10]={"program","const","type","var","integer","real","boolean","procedure","forward","function","begin","end","if","then","else","case","of","while","do","for","to","downto","repeat","until","or","div","mod","and","not","char"};
char sres[19][5]={";",".","=",":",",","+","-","'","(",")","<",">","*","/","..",":=","<=","<>",">="};
//las siguientes funciones revisan si un string pertenece a un tipo de dato
//por ejemplo entero, decimal, exponencial, etc
int esEntero(char* s){
    int i;
    int l=strlen(s);
    int l2=0;
    for(i=0;i<l;i++){
        if(isdigit(s[i])){
            l2++;
        }
    }
    if(l==l2){
        return 1;
    }
    return 0;
}
int esDecimal(char*s){
    int l=strlen(s);
    int i;
    int cantidadpuntos=0;//si esta bandera es distinto a 1, entonces no es decimal
    int digitos=0;//esta bandera debe terminal como l-1 en su valor final
    for(i=0;i<l;i++){
        if(s[i]=='.'){
            cantidadpuntos++;
        }
        if(isdigit(s[i])){
            digitos++;
        }
    }
    if((cantidadpuntos==1)&&(digitos==(l-1))){//si es distinto a 1, entonces no es decimal
        return 1;
    } 
    return 0;
    
}
int esIdentificador(char* s){
    //para que una entrada sea identificador debe cumplir con tener solo alfanumericos y _ ademas de no comenzar con un digito
    //ya que en la imagen se entiende que un identificador puede comenzar con _ o letra, luego puede terminar, contare ese caso como posible
    //es decir, _ ya es un identificador por si solo, ademas de que este caracter no es reservado ni utilizado en los simbolos, no deberia ser problema con ello
    int l=strlen(s);
    int i;
    //revisamos los casos en que no comience con una letra o con un _
    if((isalpha(s[0]))||(s[0]=='_')){//si comienza con letra o _ se revisa el resto
        int contador=0;//ya revise la primera pos pero la revisare denuevo igualmente
        for(i=0;i<l;i++){//ahora recorrere todo el string
            if((isalpha(s[i]))||('_'==s[i])||(isdigit(s[i]))){//es letra,_ o numero
                contador++;
            }
        }
        //terminado de revisar el string completo, reviso si todo concuerda
        if(contador==l){
            return 1;//si el revise todo el string y todo este concuerda con el formato, si es identificador
        }
    }
    return 0;//si no comienza con letra o _, no es identificador
    
    
    //si estaba compuesto solo por 
}
int esExpo(char*s){
    //enteroE+entero o -
    //decimalE+entero o -
    //es decir, maximo un punto, una E, 1 simbolo + o - y solamente digitos luego
    //como no se si se acepta enteroEentero , es decir sin simbolo, no lo considero valido, es decir, si o si debe llevar signo positivo o negativo
    int i;
    int l=strlen(s);
    int contadorE=0;
    int contadorPto=0;
    int contadorSigno=0;
    int contadorNumb=0;
    //al finalizar de revisar los contadores sumados deben ser = a l, contadorE, contadorSigno y contadorPto no deben ser mayores que 1
    for(i=0;i<l;i++){
        if(s[i]=='E'){//E
            if(contadorE==1){//si entra denuevo y el contador ya es 1, significa que encontro una segunda coincidencia
                return 0;
            }
            contadorE++;
        }
        if((s[i]=='+')||(s[i]=='-')){//signo
             if(contadorSigno==1){//si entra denuevo y el contador ya es 1, significa que encontro una segunda coincidencia
                return 0;
            }
            contadorSigno++;
        }
        if(s[i]=='.'){//punto
            if(contadorPto==1){//si entra denuevo y el contador ya es 1, significa que encontro una segunda coincidencia
                return 0;
            }
            contadorPto++;
        }
        if(isdigit(s[i])){//digitos
            contadorNumb++;
        }
    }
    int total=contadorE+contadorNumb+contadorPto+contadorSigno;
    //reviso igualmente que cumplan el formato
    if((contadorE==1)&&(contadorPto<2)&&(contadorSigno<2)&&(total==l)){
        return 1;
    }
    return 0;//si no cumple se retorna 0
}
//Esta funcion revisa si un string dado es valido dentro de nuestros margenes, utilizando las funciones anteriores, retornando 1 en caso de serlo
int esAlgo(char*s){
    //esta funcion es similar a revisar texto, sin embargo, esta solo retorna y no imprime nada en el archivo
    //se utiliza para no hacer una recursion con revisar texto y complicar de sobremanera el codigo
    int i;
    //primero reviso si corresponde tal cual esta a una de las palabras reservadas
    for(i=0;i<30;i++){
        if(strcmp(s,pres[i])==0){
            return 1;
        }
    }
    //ahora reviso si es un simbolo reservado
    for(i=0;i<19;i++){
        if(strcmp(s,sres[i])==0){
            return 1;
        }
    }
    //si no es ninguno de los anteriores reviso los tipos de dato
    if(esEntero(s)){
        return 1;
    }
    if(esDecimal(s)){
        return 1;
    }
    if(esIdentificador(s)){
        return 1;
    }
    if(esExpo(s)){
        return 1;
    }
    //si no calzo con nada de lo que esta permitido, entonces retorno 0
    return 0;
}
//funcion principal de mi logica, que utiliza a las anteriores para generar el archivo de salida
int revisartexto(char* s,FILE* salida){
   
    int i;
    //primero reviso si corresponde tal cual esta a una de las palabras reservadas
    for(i=0;i<30;i++){
        if(strcmp(s,pres[i])==0){
            printf("%s\n",PRES[i]);  //borrar
            fprintf(salida,"%s\n",PRES[i]);//se printea la mayuscula
            return 1;
        }
    }
    //ahora reviso si es un simbolo reservado
    for(i=0;i<19;i++){
        if(strcmp(s,sres[i])==0){
            printf("%s\n",sres[i]); //borrar
            fprintf(salida,"%s\n",sres[i]);
            return 1;
        }
    }
    //en otro caso reviso si corresponde a algun tipo de dato como identificador, digito,etc
    if(esEntero(s)){
       printf("ENTERO\n"); //borrar
        fprintf(salida,"ENTERO\n");
        return 1;
    }
    if(esDecimal(s)){
        printf("DEC\n"); //borrar
        fprintf(salida,"DECIMAL\n");
        return 1;
    }
    if(esIdentificador(s)){
       printf("IDE\n"); //borrar
        fprintf(salida,"IDENTIFICADOR\n");
        return 1;
    }
    if(esExpo(s)){
        //printf("%s es expo\n",s); //cambiar a fprint
        printf("EXPO\n"); //borrar
        fprintf(salida,"EXPONENCIAL\n");
        return 1;
    }
    //sino, reviso caracter a caracter
    //primero creare un buffer para almacenar lo leido, con el largo correspondiente +1
    int l=strlen(s);
    if(l==1){//si el largo es 1 y no entro en los casos posibles de simbolos reservados, entonces no pertenece 
        return 0;
    }
    if(l==2){//si l es 2, significa que puede ser la combinacion de dos simbolos permitidos, pero sin espaciar
    //por ende reviso cada caso en particular
        if( (s[0]==';')||(s[0]=='.')||(s[0]=='=') ||(s[0]==':') ||(s[0]==',') ||(s[0]=='+') ||(s[0]=='-') ||(s[0]==39) ||(s[0]=='(') ||(s[0]==')') ||(s[0]=='<') ||(s[0]=='>') ||(s[0]=='*') ||(s[0]=='/') ){
            //si el primer caracter es alguno de los reservador de largo 1, lo muestro
           // printf("%c y ",s[0]);//cambiar a fprint
           printf("%c\n",s[0]); //borrar
           fprintf(salida,"%c\n",s[0]);

        }
        if( (s[1]==';')||(s[1]=='.')||(s[1]=='=') ||(s[1]==':') ||(s[1]==',') ||(s[1]=='+') ||(s[1]=='-') ||(s[1]==39) ||(s[1]=='(') ||(s[1]==')') ||(s[1]=='<') ||(s[1]=='>') ||(s[1]=='*') ||(s[1]=='/') ){
            //si el primer caracter es alguno de los reservador de largo 1, lo muestro
            //printf("%c\n",s[1]);//cambiar a fprint
            printf("%c\n",s[1]); //borrar
            fprintf(salida,"%c\n",s[1]);
        }

        return 0;//si entro en los casos que corresponde solo saldra.
    }
    //ahora si el largo es mayor a 3 pueden ser combinaciones tales como do; o ;;; en tal caso se leera char x char almacenando en el buffer
    char* buffer=(char*)malloc(sizeof(char)*(l+2));
    char* bufferaux=(char*)malloc(sizeof(char)*(l+2));
    //con esto revisare los casos donde vengan cosas juntas por ejemplo for123, entregando en el archivo de salida FOR\nENTERO\n
    int bLargo=strlen(buffer);//aqui el largo es 0
    int bLargoaux=strlen(bufferaux);//aqui el largo es 0
    //para asegurar que ambos buffers no tengan datos los vaciare a mano
    strcpy(buffer,"");
    strcpy(bufferaux,"");
    char auxchar1,auxchar2;
    fflush(stdout);//por alguna razon cuando entraba a leer en esta zona stdout venia con info sucia
    //hago la primera lectura a mano ya que por alguna razon con el for me daba problemas.
    auxchar1=s[0];
    strncat(bufferaux,&auxchar1,1);
    if (esAlgo(bufferaux))
    {
        strncat(buffer,&auxchar1,1);
    }
    i=1;
    l++;//aumento en 1 el l ya que ha dado problemas por falta de rango sin razon alguna
    while(i!=l){
        //leido un caracter, reviso si tengo algo actualmente
        auxchar1=s[i];
        strncat(bufferaux,&auxchar1,1);
        if(esAlgo(bufferaux)){
            //si lo leido cumple con el formato, revisare el siguiente en caso de que este igual cumpla
            //es decir si tengo en el buffer aux "123" y el string es "1234", "123" cumple el formato, pero 1234 tambien y es de mayor
            //tamanio
            strncat(buffer,&auxchar1,1);
            auxchar2=s[i+1];
            strncat(bufferaux,&auxchar2,1);
            if(esAlgo(bufferaux)){
                //si este caso se cumple, entonces añado al buffer 
                
            }else{
                //si al agregar una posicion mas, no cumple ningun formato se printea
                //y se reinician los buffers
                printf("%s BUFFER\n",buffer); //borrar
                fprintf(salida,"%s\n",buffer);

                strcpy(buffer,"");
                strcpy(bufferaux,"");
            }
        }else{

            strcpy(bufferaux,"");
        }
        i++;
    }
    //esto es igual que el while de arriba pero por alguna razon no funcionaba el 100% de las pruebas que hice 
   /* for(i=1;i<l;i++){
        //leido un caracter, reviso si tengo algo actualmente
        auxchar1=s[i];
        strncat(bufferaux,&auxchar1,1);
        if(esAlgo(bufferaux)){
            //si lo leido cumple con el formato, revisare el siguiente en caso de que este igual cumpla
            //es decir si tengo en el buffer aux "123" y el string es "1234", "123" cumple el formato, pero 1234 tambien y es de mayor
            //tamanio
            strncat(buffer,&auxchar1,1);
            auxchar2=s[i+1];
            strncat(bufferaux,&auxchar2,1);
            if(esAlgo(bufferaux)){
                //si este caso se cumple, entonces añado al buffer 
                
            }else{
                //si al agregar una posicion mas, no cumple ningun formato se printea
                //y se reinician los buffers
                //fprint buffer
                strcpy(buffer,"");
                strcpy(bufferaux,"");
            }
        }else{

            strcpy(bufferaux,"");
        }
        

        
    }*/
    //ahora que ya esta terminado el archivo de salida, se cierra y se liberan los buffers
    fflush(stdin);
    fflush(stdout);
    return 0;
}
FILE * leerArchivo(char* nombreArchivo){
    FILE* archivo = NULL;
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL){
        return 0;
    } else {
        return(archivo);
    }
}

int existeArchivo(char* nombreArchivo){
    FILE* archivo = NULL;
    archivo = fopen(nombreArchivo, "r"); 
    if (archivo == NULL){ 
        return 0;
    } 
    return 1;

}
void crearArchivoSalida(FILE * archivoEntrada, char* nombreArchivoSalida){
    
    char texto[100];
    int resultado;
    FILE * salida;
    salida = fopen(nombreArchivoSalida, "w");//creo el archivo de salida
    while(fscanf(archivoEntrada,"%s",&texto)!= EOF) {

        resultado=revisartexto(texto,salida);
        
    }
    fclose(archivoEntrada);
    fclose(salida);
}

int main(int argc,char* argv[]) {

    //Se verifica que se hayan ingresado dos parametros de entrada
    if(argc == 1){
        printf("Error: Faltan par%cmetros.\n", 160);
        printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
        return 0;
    }
    //En caso falte un parametro
    if(argc == 2) {
        printf("Error: Falta par%cmetro.\n", 160);
        printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
        return 0;
    }
    //En caso que se hayan ingresado parametros extra
    if(argc > 3) {
        printf("Demasiados par%cmetros.\n", 160);
        printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
        return 0;
    }

    FILE* archivoEntrada = leerArchivo(argv[1]);

    //Si la funcion leerArchivo devuelve un 0 es porque el archivo no existe o el nombre fue mal ingresado.
    if(archivoEntrada == 0){
        printf("Error: El archivo de entrada no existe.\n");
        return 0;
    }
    //Se verifica en caso el archivo de salida ya exista
    
    if(existeArchivo(argv[2]) == 1){
        printf("Error: El archivo de salida ya existe.\n");
        return 0;
    }
    
    //Se escribe el archivo de salida
    crearArchivoSalida(archivoEntrada,argv[2]);
    
    return 0;
}