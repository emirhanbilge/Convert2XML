#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Element
{
    char elementName[50];
};

struct Elements
{
    struct Element allElementNames[20];
};

static int id = 1;
static struct Elements elementList, writeEmpty;
static struct Element tempElement;
static char root[25];
static int elementNumber = 0;

void comman(char line[], char splitValue, bool elementOrNot) //delete endline or creating elements
{
    for (int i = 0; i < 128; i++)
    {
        if (line[i] == ' ' && elementOrNot)
        {
            line[i] = '_';
        }
        if (line[i] == splitValue)
        {
            line[i] = '\n';
        }
    }
    FILE *fp = fopen("program.txt", "w");
    fprintf(fp, line);
    fclose(fp);
}

void delete (char tempElementName[])
{
    for (int i = 0; i < 128; i++)
    {
        if (tempElementName[i] == '\n' || tempElementName[i] == '\r') //does not matter Unix or Windows
        {
            tempElementName[i] = '\0'; //Null
            break;
        }
    }
}

void elements(char line[], char splitValue, bool flag)
{
    int count = 0;
    struct Elements e;
    comman(line, splitValue, true); // clear space in element
    FILE *fp = fopen("program.txt", "r");
    char tempLine[128];
    while (fgets(tempLine, sizeof(tempLine), fp) != NULL)
    {
        strcpy(tempElement.elementName, tempLine);
        e.allElementNames[count] = tempElement;
        delete (e.allElementNames[count].elementName);
        count++;
        if (flag)
        {
            elementNumber++;
            elementList = e;
        }
    }
    if (!flag)
    {
        writeEmpty = e;
    }
    fclose(fp);
}

void write_xml(char line[], char splitValue, char output[])
{
    elements(line, splitValue, false); // get elements information

    //write operations all
    FILE *fp2 = fopen(output, "a");
    if (id == 1)
    {
        fprintf(fp2, "%s%s%s%s%s%s", "<?xml version=\"1.0\" encoding= \"utf-8\" ?>\n", "<", root, ">", "\n", "\t<UTF_encoded>\n");
    }
    fprintf(fp2, "\t\t%s%d%s", "<row id='", id, "'>\n");
    for (int i = 0; i < elementNumber; i++)
    {
        delete (writeEmpty.allElementNames[i].elementName);
        fprintf(fp2, "\t\t\t%s%s%s%s%s%s%s%s", "<", elementList.allElementNames[i].elementName, ">", writeEmpty.allElementNames[i].elementName, "</", elementList.allElementNames[i].elementName, ">", "\n");
    }
    fprintf(fp2, "\t\t%s", "</row>\n");
    id++;
    fprintf(fp2, "\n");
    fclose(fp2);
}

int main(int argc, char *args[])
{
    printf("%s%s%s%s%s%s%s",
           "\nUsing like Contacts.csv Contacts.xml -separator 1 -opsys 1 \n\n",
           "\t\t\t\tCreated by EBB(Emirhan Bilge Bulut 2017510020 \n\n",
           "input.csv(you can write also txt or some specific text editor)",
           "outputname.xml (you can also write txt format)\n",
           "-separator defines separator between each datum (1=comma, 2=tab, 3=semicolon if you write wrong program  default 1st option) \n",
           "It runs on Unix-based operating systems (MacOs and Linux) and Windows.For using help  (-h), you must write if you dont use , you can't write \n",
           "-h print information to screen about how other arguments can be used.\n\n");
    char splitValue;
    if (argc < 5)
    {
        printf("ERROR MESSEGA !!! \n\n");
        exit(-1);
    }
    if (argc >7)
    {
            printf("%s%s%s", "Supported : \n.dat \n", ".csv \n", ".txt");
    }
    if (args[4][0] == '3')
    {
        splitValue = ';';
    }
    else if (args[4][0] == '2')
    {
        splitValue = '\t';
    }
    else
    {
        splitValue = ','; //default split value
    }
    FILE *fp = fopen(args[1], "r");
    char line[128];
    for (int i = 0; i < 25; i++)
    {
        if (args[1][i] == '.')
        {
            break;
        }
        else
        {
            root[i] = args[1][i]; // Create xml root
        }
    }
    fgets(line, sizeof(line), fp);
    elements(line, splitValue, true); //Create Elements
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        write_xml(line, splitValue, args[2]); // getting informations
    }
    FILE *fp2 = fopen(args[2], "a");
    fprintf(fp2, "%s%s%s%s", "\t</UTF_encoded>\n", "</", root, ">\n");
    remove("program.txt");
    fclose(fp);
    return 0;
}

///UTF-8 Encoding References ->>> https://support.crossref.org/hc/en-us/articles/215652783-Special-characters-in-your-XML
// Created by EBB ® (Emirhan Bilge Bulut)