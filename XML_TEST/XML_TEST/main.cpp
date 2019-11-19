#include "tinyxml.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;
void loadXML(){
	TiXmlDocument doc;//申明一个文档类型变量，用来存储读取的xml文档
	if (!doc.LoadFile("a.xml"))	//检测xml文档是否存在
	{
		cerr << doc.ErrorDesc() << endl;
	}
	TiXmlElement* root = doc.FirstChildElement();//指向xml文档的根元素
	if (root == NULL)//检测根元素存在性		
	{
		cerr << "Failed to load file: No root element." << endl;
		doc.Clear();
	}
	//elem指向根的第一个孩子元素
	for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
		const char* arr = elem->Attribute("priority"); //通过元素属性寻找元素
		if (strcmp(arr, "1") == 0){	
			TiXmlElement* elem1 = elem->FirstChildElement();
			TiXmlNode* node = elem1->FirstChild();//node指向elem1元素下的文本
			cout << node->Value() << endl;
		}
		string sTmp = elem->Value();
		if (strcmp(elem->Value(), "Item1") == 0){ //也可以通过元素名寻找元素
			TiXmlNode* node = elem->FirstChild();
			cout << node->Value() << endl;
		}
	}
}

TiXmlElement * GetValue( TiXmlElement * cTiXml , vector<string> sPath , int nVectorID , bool &bRead )
{
	bRead = false ;
	for (TiXmlElement* elem = cTiXml->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		string sTmp = elem->Value() ;
		if ( sTmp == sPath.at(nVectorID) )
		{
			if ( sPath.size() <= nVectorID+1 )
			{
				bRead = true ;
				return elem ;
			}
			else
			{
				bool bTmp = false ;
				TiXmlElement* cTmp = GetValue( elem , sPath , nVectorID+1 , bTmp );
				if ( bTmp )
				{
					bRead = true ;
					return cTmp ;
				}
				else
				{
					bRead = false ;
					return nullptr ;
				}
			}
			break;
		}
	}

	return nullptr ;
}

void loadXML1()
{
	TiXmlDocument doc;//申明一个文档类型变量，用来存储读取的xml文档
	if (!doc.LoadFile("Axis.xml"))	//检测xml文档是否存在
	{
		cerr << doc.ErrorDesc() << endl;
	}
	TiXmlElement* root = doc.FirstChildElement();//指向xml文档的根元素
	if (root == NULL)//检测根元素存在性		
	{
		cerr << "Failed to load file: No root element." << endl;
		doc.Clear();
	}
	vector <string> vTmpPath ;
	vTmpPath.push_back( "AXIS_X" );
	vTmpPath.push_back( "SPEED" );
	vTmpPath.push_back( "POS" );
	vTmpPath.push_back( "VEL" );

	bool bTmp = false ;
	TiXmlElement* cTmpAim = GetValue( root , vTmpPath , 0 , bTmp );//指向xml文档的根元素

	TiXmlNode* node = cTmpAim->FirstChild();//node指向elem1元素下的文本

	string sTmpValue = node->Value() ; 
	cout << sTmpValue << endl;

	Sleep(100);
}
 
bool SaveXml( )
{
	TiXmlDocument doc;

	if (!doc.LoadFile("madeByHand.xml"))	//检测xml文档是否存在
	{
		cerr << doc.ErrorDesc() << endl;
	}

// 	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "ASCII", "" );
// 	doc.LinkEndChild( decl );

	TiXmlElement * element = doc.FirstChildElement();
	TiXmlNode * cTmp = element->FirstChild();
	cTmp->SetValue( "ggg" );


	doc.SaveFile( "madeByHand.xml" );

	return true;

}

/*
string GetValue( TiXmlDocument * cTiXml , vector<string> sPath , string sDefeat , bool &bRead )
{
	bRead = false ;

	if ( cTiXml == nullptr )
	{
		return sDefeat ;
	}

	for ( int i = 0 ; i < sPath.size() ; i ++ )
	{

	}



	return sDefeat ;
}

*/

int main(int argc, char* argv[])
{
	SaveXml();
	system("pause");
	return 0;
}