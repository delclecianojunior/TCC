#include <UIPEthernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[] = {192, 168, 1, 101}; // Coloquei o ultimo sendo 2 porque o que finalizava coms ja estava separado pro gateway

EthernetServer server(80);

int sensorChuvaPin = 7;
int botaoAbrir = 8;
int statusBotaoAbrir = 0;
int botaoFechar = 9;
int statusBotaoFechar = 0;

String readString = String(30);

void setup()
{
    Ethernet.begin(mac, ip);
    server.begin();
    pinMode(botaoAbrir, OUTPUT);
    pinMode(botaoFechar, OUTPUT);
    // Janela inicia fechada
    statusBotaoAbrir = 0;
    statusBotaoFechar = 0;
    digitalWrite(botaoAbrir, LOW);
    digitalWrite(botaoFechar, HIGH);
    pinMode(sensorChuvaPin, INPUT);
    //Serial.begin(3600);
}

void loop()
{
    if (VerificarSeEstaChovendo()) //Se esta chovendo ele fecha a janela , mas so se ela tiver aberta
    {
        _fecharJanela();
    }

    bool estaChovendo = VerificarSeEstaChovendo();

    EthernetClient client = server.available();

    if (!client)
        return;

    while (client.connected())
    {
        if (!client.available())
            return;

        char c = client.read();
        lerValoresDaRequisicao(client, c);

        if (c == '\n')
        {
            controlarJanela();

            construirCorpoDaPagina(client);

            construirBotaoAbrir(client);
            construirBotaoFechar(client);

            construirTextoEstadoDaJanela(client);

            construirFinalDaPagina(client);

            resetarString();

            client.stop();
        }
    }
}

void lerValoresDaRequisicao(EthernetClient client, char c)
{
    if (readString.length() < 100)
        readString += c;
}

void controlarJanela()
{
    abrirJanela();
    fecharJanela(); //esta invocando o metodo do fecha janela da interface web , o que esta com underline e o do sensor
}

void abrirJanela() 
{
    if (readString.indexOf("abrir=1") > 0)
    {
        digitalWrite(botaoAbrir, HIGH);
        statusBotaoAbrir = 1;

        digitalWrite(botaoFechar, LOW);
        statusBotaoFechar = 0;
    }
}

void fecharJanela() // fecha a janela pelo html ou melhor pela interface web
{
    if (readString.indexOf("abrir=0") > 0)
    {
        _fecharJanela();
    }
}

void _fecharJanela()
{
    digitalWrite(botaoFechar, HIGH);
    statusBotaoFechar = 1;

    digitalWrite(botaoAbrir, LOW);
    statusBotaoAbrir = 0;
}

void construirBotaoAbrir(EthernetClient client)
{
    if (statusBotaoAbrir == 1)
    {
        client.println("<center><form method=get name=ABRIR><input type=submit disabled value=ABRIR></form></center>");
    }
    else if (statusBotaoAbrir == 0)
    {
        client.println("<center><form method=get name=ABRIR><input type=hidden name=abrir value=1 /><input type=submit value=ABRIR></form></center>");
    }
}

void construirBotaoFechar(EthernetClient client)
{
    if (statusBotaoFechar == 1)
    {
        client.println("<center><form method=get name=FECHAR><input type=submit disabled value=FECHAR></form></center>");
    }
    else if (statusBotaoFechar == 0)
    {
        client.println("<center><form method=get name=FECHAR><input type=hidden name=abrir value=0 /><input type=submit value=FECHAR></form></center>");
    }
}

void construirTextoEstadoDaJanela(EthernetClient client)
{
    client.println("<center><font size='5'>Estado atual da janela: </center>");

    if (statusBotaoAbrir == 1)
        client.println("<center><font color='green' size='5'>ABERTA</center>");
    else
        client.println("<center><font color='red' size='5'>FECHADA</center>");
}

void resetarString()
{
    readString = "";
}

void construirCorpoDaPagina(EthernetClient client)
{
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println("<body style=background-color:#ADD8E6>");
    client.println("<center><font color='blue'><h1>Janela inteligente<h1></font></center>");
    client.println("<h1><center>Controle da acionamento</center></h1>");
}

void construirFinalDaPagina(EthernetClient client)
{
    client.println("</body></html>");
}

bool VerificarSeEstaChovendo()
{
    int valorUmidadeDigital = digitalRead(sensorChuvaPin);
    if (valorUmidadeDigital <= 0)
        return true;

    return false;
}
