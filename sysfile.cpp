#include "sysfile.h"

#include "qwidget.h"
#include "qfile.h"
#include "qdebug.h"
#include <QDomDocument>
#include <qtextcodec.h>
#include <QMessageBox>

sysfile::sysfile(QObject *parent) : QObject(parent)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
}

void sysfile::create_sysfile(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"GB2312\"");
    doc.appendChild(instruction);
    QDomElement root=doc.createElement("sysparam");
    doc.appendChild(root);
    QDomElement ele=doc.createElement("systag");
    root.appendChild(ele);
    QDomText text=doc.createTextNode("blank");
    ele.appendChild(text);
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}

QString sysfile::load_sysparam(char* arg,...)
{
    QString ret="";
    QStringList strlist;
    QString str;
    va_list pDebug;
    va_start(pDebug,arg);
    str=QString(QLatin1String(arg));
    while(str!=""){
        strlist.append(str);
        char* var=va_arg(pDebug,char *);
        str=QString(QLatin1String(var));
    };

    if(strlist.size()<1)
    {
        QMessageBox::information(NULL,"Error","No enough load input parameters!",QMessageBox::Ok);
        return ret;
    }

    QString filename="sysconfig.xml";
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly|QFile::Text))
    {
        QMessageBox::information(NULL,"Error","Open sysfile failed!",QMessageBox::Ok);
        return ret;
    }

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        QMessageBox::information(NULL,"Error","Set content failed!",QMessageBox::Ok);
        return ret;
    }
    file.close();


    QDomElement root=doc.documentElement();

    QDomElement ele_point=root.firstChildElement();
    int elefound=0;
    while(!ele_point.isNull())
    {
        if(ele_point.tagName()==strlist.at(0))
        {
            elefound=1;
            break;
        }
        else
        {
            ele_point=ele_point.nextSiblingElement();
        }
    }
    if(elefound==0)
    {
        //QMessageBox::information(NULL,"Error","Cannot find param!",QMessageBox::Ok);
        return ret;
    }
    for(int strlistlen=strlist.size()-1;strlistlen>0;strlistlen--)
    {
        elefound=0;
        if(ele_point.firstChildElement().isNull())
        {
            //QMessageBox::information(NULL,"Error","Cannot find param!",QMessageBox::Ok);
            return ret;
        }
        else
        {
            ele_point=ele_point.firstChildElement();
            while(!ele_point.isNull())
            {
                if(ele_point.tagName()==strlist.at(strlist.size()-strlistlen))
                {
                    elefound=1;
                    break;
                }
                else
                {
                    ele_point=ele_point.nextSiblingElement();
                }
            }
        }
        if(elefound==0)
        {
            //QMessageBox::information(NULL,"Error","Cannot find param!",QMessageBox::Ok);
            return ret;
        }
    }
    if(ele_point.firstChild().isNull())
    {
        //QMessageBox::information(NULL,"Error","Cannot find param!",QMessageBox::Ok);
        return ret;
    }
    else
    {
        ret=ele_point.firstChild().nodeValue();
        return ret;
    }
}

void sysfile::save_sysparam(char* arg,...)
{
    QStringList strlist;
    QString str;
    va_list pDebug;
    va_start(pDebug,arg);
    str=QString(QLatin1String(arg));
    while(str!=""){
        strlist.append(str);
        char* var=va_arg(pDebug,char*);
        str=QString(QLatin1String(var));
    };

    if(strlist.size()<2)
    {
        QMessageBox::information(NULL,"Error","No enough save input parameters!",QMessageBox::Ok);
        return;
    }

    QString filename="sysconfig.xml";
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly|QFile::Text))
    {
        create_sysfile(filename);
    }

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        QMessageBox::information(NULL,"Error","Set content failed!",QMessageBox::Ok);
        return;
    }
    file.close();


    QDomElement root=doc.documentElement();
    if(root.tagName()!="sysparam")
    {
        QMessageBox::information(NULL,"Error","Incorrect Save sysfile!",QMessageBox::Ok);
        return;
    }

    QDomElement ele_tmp[strlist.size()-1];
    QDomElement ele_point=root.firstChildElement();
    int elefound=0;
    while(!ele_point.isNull())
    {
        if(ele_point.tagName()==strlist.at(0))
        {
            elefound=1;
            ele_tmp[0]=ele_point;
            break;
        }
        else
        {
            ele_point=ele_point.nextSiblingElement();
        }
    }
    if(elefound==0)
    {
        ele_tmp[0]=doc.createElement(strlist.at(0));
        root.appendChild(ele_tmp[0]);
        ele_point=root.firstChildElement();
        while(ele_point.tagName()!=strlist.at(0))
            ele_point=ele_point.nextSiblingElement();
    }
    for(int strlistlen=strlist.size()-1;strlistlen>1;strlistlen--)
    {
        elefound=0;
        if(ele_point.firstChildElement().isNull())
        {
            ele_tmp[strlist.size()-strlistlen]=doc.createElement(strlist[strlist.size()-strlistlen]);
            ele_tmp[strlist.size()-strlistlen-1].appendChild(ele_tmp[strlist.size()-strlistlen]);
            ele_point=ele_point.firstChildElement();
            elefound=1;
        }
        else
        {
            ele_point=ele_point.firstChildElement();
            while(!ele_point.isNull())
            {
                if(ele_point.tagName()==strlist.at(strlist.size()-strlistlen))
                {
                    elefound=1;
                    ele_tmp[strlist.size()-strlistlen]=ele_point;
                    break;
                }
                else
                {
                    ele_point=ele_point.nextSiblingElement();
                }
            }
        }
        if(elefound==0)
        {
            ele_tmp[strlist.size()-strlistlen]=doc.createElement(strlist[strlist.size()-strlistlen]);
            ele_tmp[strlist.size()-strlistlen-1].appendChild(ele_tmp[strlist.size()-strlistlen]);
            ele_point=ele_tmp[strlist.size()-strlistlen-1].firstChildElement();
            while(ele_point.tagName()!=strlist.at(strlist.size()-strlistlen))
                ele_point=ele_point.nextSiblingElement();
        }
    }
    if(ele_point.firstChild().isNull())
    {
        QDomText textnode=doc.createTextNode(strlist.at(strlist.size()-1));
        ele_point.appendChild(textnode);
    }
    else
    {
        ele_point.firstChild().setNodeValue(strlist.at(strlist.size()-1));
    }

    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::information(NULL,"Error","sysfile open error!",QMessageBox::Ok);
        return;
    }
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}
