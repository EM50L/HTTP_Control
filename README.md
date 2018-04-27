# HTTP_Control

Borja HTTP_Control

Bueno hace unos dias Recibi una llamada de un amigo con una idea de un proyecto

Para sus Alumnos.

La Idea es controlar un Arduino por peticiones HTTP

**Con 39Lineas (primera version)**

Para luego integrarlo en algo MAS GRANDE

(esto ya es su parte y de momento no se puede contar.)

# Manejo:

## 1) Conectarnos a la red wifi creada por el ESP8266

Una Vez Encendido el ESP8266 aparecera una red WIFI llamada ESP

## 2) Abrir el navegador y teclear la siguiente direccion: **http.//192.168.4.1**

## 3) Pulsar en el enlace de encender/apagar led.

el led deberia responder.

# Explicacion:

## 1) El programa crea una RED WIFI llamada ESP

```c
WiFi.mode(WIFI_AP);
WiFi.softAP("ESP");
```

## 2) Despues Arranca un servidor web con 3 paginas.

```c
servidor_web.on("/LedOn" , D4a0 );//en la placa WEMOS d1 mini 
servidor_web.on("/LedOff" , D4a1 );// el led se enciende al poner D4 a 0
servidor_web.on("/" , pag_principal);
servidor_web.begin();

```

## 3) Muestra via serie la Direccion (esto es informativo)

```c
Serial.println("\n\n Iniciando Red WIFI ESP... ");
Serial.println(" http://192.168.4.1 ");
```

## 4) El truco esta en la combinacion de las funciones y las paginas del servidor.

```c
servidor_web.on("/LedOn" , D4a0 );
```

Quiere decir que al abrir la direccion http://192.168.4.1/LedOn
se lanzara una llamada a la funcion __D4a0()__ 
que encendera el led.

( en la placa Wemos D1 el led se enciende al poner D4 a 0 )

```c
void D4a0() {
  pinMode(D4, OUTPUT);
  digitalWrite(D4, 0);
  servidor_web.send(200, "text/plain", "Ok D4=0");
}
```

En esta funcion Enciendo el LED poniendo el pin D4 a 0.

```c
pinMode(D4, OUTPUT);
digitalWrite(D4, 0);
```

Y muesto resultado.
```c
servidor_web.send(200, "text/plain", "Ok D4=0");
```

### En la proxima revision añadire:

- que se pueda conectar a un wifi

- que se pueda leer una patilla analogica (A0)

Asi el programa deberia ser totalmente funcional.

# Continuando con HTTP_control|

Esta vez añado Conexion a una red wifi existente y lectura del Pin A0.

## Manejo:

## 1) Conectar el ESP al USB del PC y abrir terminal serie del arduino para ver la IP que obtiene al conctarse al WIFI

###1b) O Con el movil y el programa libre **Port Autority** (por ejemplo) ver la IP que obtiene el ESP al conectarse al wifi. 

## 2) Con el ordenador o el movil conectado al mismo wifi 

poner en el navegador la IP indcada en el terminal.

## 3) Esta vez si pulsamos en leer A0 

al refrescar la pagina veremos com el valor cambia al tocar el pin A0 con el dedo.

(al ser un entrada analogica es bastante sensible)

# Explicacion:

## 1) El programa se conecta a una red wifi llamada Mi_Red_WIFI (cambiar por el nombre de la red wifi a la que nos queremos conectar)

```c
char* Red_WIFI = "Mi_Red_WIFI";
char* password_WIFI = "Mi_Contraseña_Wifi";
WiFi.mode(WIFI_AP_STA);
WiFi.softAP("ESP");
WiFi.begin(Red_WIFI, password_WIFI);
```

he cambiado WIFI_AP por WIFI_AP_STA 

(AP = punto de acceso) (STA de estacion)

he añadido WiFi.begin(Red_WIFI, password_WIFI);

Para que se conecte a la red WIFI

## 2) Pasados 5 segundos muestro la ip obtenida WiFi.localIP()

```c
delay(5000); //tiempo para que conecte al WIFI
Serial.print(F("http://")); 
Serial.println(WiFi.localIP().toString());
```
