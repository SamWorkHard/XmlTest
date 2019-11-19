#include "tinyxml.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;
void loadXML(){
	TiXmlDocument doc;//����һ���ĵ����ͱ����������洢��ȡ��xml�ĵ�
	if (!doc.LoadFile("a.xml"))	//���xml�ĵ��Ƿ����
	{
		cerr << doc.ErrorDesc() << endl;
	}
	TiXmlElement* root = doc.FirstChildElement();//ָ��xml�ĵ��ĸ�Ԫ��
	if (root == NULL)//����Ԫ�ش�����		
	{
		cerr << "Failed to load file: No root element." << endl;
		doc.Clear();
	}
	//elemָ����ĵ�һ������Ԫ��
	for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
		const char* arr = elem->Attribute("priority"); //ͨ��Ԫ������Ѱ��Ԫ��
		if (strcmp(arr, "1") == 0){	
			TiXmlElement* elem1 = elem->FirstChildElement();
			TiXmlNode* node = elem1->FirstChild();//nodeָ��elem1Ԫ���µ��ı�
			cout << node->Value() << endl;
		}
		string sTmp = elem->Value();
		if (strcmp(elem->Value(), "Item1") == 0){ //Ҳ����ͨ��Ԫ����Ѱ��Ԫ��
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
	TiXmlDocument doc;//����һ���ĵ����ͱ����������洢��ȡ��xml�ĵ�
	if (!doc.LoadFile("Axis.xml"))	//���xml�ĵ��Ƿ����
	{
		cerr << doc.ErrorDesc() << endl;
	}
	TiXmlElement* root = doc.FirstChildElement();//ָ��xml�ĵ��ĸ�Ԫ��
	if (root == NULL)//����Ԫ�ش�����		
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
	TiXmlElement* cTmpAim = GetValue( root , vTmpPath , 0 , bTmp );//ָ��xml�ĵ��ĸ�Ԫ��

	TiXmlNode* node = cTmpAim->FirstChild();//nodeָ��elem1Ԫ���µ��ı�

	string sTmpValue = node->Value() ; 
	cout << sTmpValue << endl;

	Sleep(100);
}
 
bool SaveXml( )
{
	TiXmlDocument doc;

	if (!doc.LoadFile("madeByHand.xml"))	//���xml�ĵ��Ƿ����
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