#pragma once
#include<string>
#include <limits>
#include<queue>
#include <vector>


using namespace std;

void TestGraph();

// �ڽӾ���ÿһ����Ԫ�ɱ�ʾһ���ߵ���Ϣ
class GraphAdjMat {
	struct ArcCell    // �洢����Ϣ�Ľṹ��
	{
		int adj;   // �ڽӶ����ϵ��ͼ��0|������ 1|���� ����(��Ȩͼ)�����INT_MAX��|������  Ȩֵ��W��|����
		string info;   // �ߣ�������Ϣ
	};
public:
	struct ArcData         // ���������һ���ṹ��
	{
		string tail;   // ��β
		string head;   // ��ͷ
		int weight;    // Ȩ��
	};
	enum Graphtype
	{
		DG,        // ������Ȩͼ
		UDG,	   // ������Ȩͼ
		DN,		   // ������Ȩͼ(������)
		UDN        // ������Ȩͼ(������)
	};

private:
	const int INF = INT_MAX;   // �����
	static const int MAX_VERTEX_NUM = 10;  //֧�ֵ���ඥ����

	// ��̬�洢�ṹ
	string vexs[MAX_VERTEX_NUM];    // �����
	ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   // �߾���
	int vexNum;          // ������
	int arcNum;          // ����
	int type;            // ͼ����
	int nonAdjInt;      // ������intֵ��0��Ȩ| ����|��Ȩ
	
	queue<int>* vexNullIndexQueue = new queue<int>; //���������пն���λ���������� ����Ҫ���٣�
	bool vexVisited[MAX_VERTEX_NUM];  //������ʱ�����飺0|δ���� 1|�ѷ���

	void CreateDG(vector<ArcData*>* arcsList);
	void CreateUDG(vector<ArcData*>* arcsList);
	void CreateDN(vector<ArcData*>* arcsList);
	void CreateUDN(vector<ArcData*>* arcsList);

	int Locate(string vex);  // ��λ����Ԫ��λ��
	void DFS_R(int vex);  // �ݹ�������ȱ���

public:
	GraphAdjMat(int type);  // ���캯������ʼ��ͼ����
	~GraphAdjMat();
	
	void Init(vector<string>* vexs, vector<ArcData*>* arcLists); // ��ʼ�����㡢������
	void Display();
	void InsertVertex(string v);   // ���붥��
	void DeleteVertex(string v);   // ɾ������
	void InsertArc(ArcData* arc);  // �����
	void DeleteArc(ArcData* arc);  // ɾ����
	void Display_DFS(string v);   // ��ָ�����㿪ʼ������ȱ���
	void Display_BFS(string v);   // ��ָ�����㿪ʼ������ȱ���


	GraphAdjMat* MiniSpanTree_Prim(string vertex);		//��С��������Prim �㷨��
	GraphAdjMat* MiniSpanTree_Kruskal(string vertex);	//��С��������Kruskal �㷨��

};
