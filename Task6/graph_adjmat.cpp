#include "graph_adjmat.h"
#include <iostream>

using namespace std;

GraphAdjMat::GraphAdjMat(int type) {
	this->type = type;
	this->vexNum = 0;
	this->arcNum = 0;
	if (this->type == DG || this->type == UDG) {
		this->nonAdjInt = 0;  //ͼ�Ĳ�����intֵ0
	}
	else{
		this->nonAdjInt = this->INF; // ���Ĳ�����intֵ�����
	}
}

GraphAdjMat::~GraphAdjMat() {
	// �ͷŶ����λ����������
	while (!vexNullIndexQueue->empty()) {  // �ǿ�
		vexNullIndexQueue->pop();
	}
	delete vexNullIndexQueue;
}

void GraphAdjMat::Init(vector<string>* vexs, vector<ArcData*>* arcLists) {
	//��ʼ�����㡢�����ݣ������� ͼ | ��
	//��Σ�
	//vexs: ���� �б�
	//arcsList : ������ �б�
	
	//1.��ʼ����������
	if (vexs->size() > MAX_VERTEX_NUM) {
		return;
	}
	for (int i = 0; i < vexs->size(); i++) {
		this->vexs[i] = vexs->at(i);
	}
	this->vexNum = vexs->size();
	//1.1��ʼ����������ն���λ����������
	// ʣ�¿����õĶ���������ŵ������Ա���ʱ֮��
	for (int i = vexs->size(); i < MAX_VERTEX_NUM; i++) {  
		this->vexNullIndexQueue->push(i);
	}
	//2.���ݳ�ʼ�����ͣ�����ָ�����͵�ͼ
	switch (this->type)
	{
	case DG:
		CreateDG(arcLists);  break;
	case UDG:
		CreateUDG(arcLists); break;
	case DN:
		CreateDN(arcLists);  break;
	case UDN:
		CreateUDN(arcLists); break;
	default:
		break;
	}
}

// ����������Ȩͼ 
void GraphAdjMat::CreateDG(vector<ArcData*>* arcsList) {
	//�������ڹ�ϵ��0|������ 1|����
	//�ڽӾ���Ϊ �ǶԳƾ���

	//��ʼ����ʱ�߶���
	ArcData *arcData = nullptr;
	// ��ʼ����ά��������
	int m = 0, n = 0;
	// ��ʼ���ߵ��ڽӾ���
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			this->arcs[i][j].adj = 0; // ������
		}
	}
	// �����������б�
	for (int i = 0; i < arcsList->size(); i++) {
		arcData = arcsList->at(i); // �����ȡ��
		// ��λ�ߵ����˶����λ��, mָ��n
		m = Locate(arcData->tail);
		n = Locate(arcData->head);
		// ���ö�������Ϊ1��
		if (this->arcs[m][n].adj == 1) {
			continue;  //ȥ���ظ���
		}
		this->arcs[m][n].adj = 1;
		this->arcNum++; // �߼���
	}
}

// ����������Ȩͼ 
void GraphAdjMat::CreateUDG(vector<ArcData*>* arcsList) {
	//�������ڹ�ϵ��0|������ 1|����
	//�ڽӾ���Ϊ �Գƾ���

	//��ʼ����ʱ�߶���
	ArcData* arcData = nullptr;
	// ��ʼ����ά��������
	int m = 0, n = 0;
	// ��ʼ���ߵ��ڽӾ���
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			this->arcs[i][j].adj = 0; // ������
		}
	}
	// �����������б�
	for (int i = 0; i < arcsList->size(); i++) {
		arcData = arcsList->at(i); // �����ȡ��
		// ��λ�ߵ����˶����λ��, mָ��n
		m = Locate(arcData->tail);
		n = Locate(arcData->head);
		// ���ö�������Ϊ1��
		if (this->arcs[m][n].adj == 1 || this->arcs[n][m].adj == 1) {
			continue;  //ȥ���ظ���
		}
		this->arcs[m][n].adj = 1;
		this->arcs[n][m].adj = 1;
		this->arcNum++; // �߼���
	}
}

// ����������Ȩͼ 
void GraphAdjMat::CreateDN(vector<ArcData*>* arcsList) {
	//�������ڹ�ϵ��INF|������ w|����
	//�ڽӾ���Ϊ �ǶԳƾ���

	//��ʼ����ʱ�߶���
	ArcData* arcData = nullptr;
	// ��ʼ����ά��������
	int m = 0, n = 0;
	// ��ʼ���ߵ��ڽӾ���
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			this->arcs[i][j].adj = this->INF; // ������
		}
	}
	// �����������б�
	for (int i = 0; i < arcsList->size(); i++) {
		arcData = arcsList->at(i); // �����ȡ��
		// ��λ�ߵ����˶����λ��, mָ��n
		m = Locate(arcData->tail);
		n = Locate(arcData->head);
		// ���ö�������ΪȨ��weight��
		if (this->arcs[m][n].adj != this->INF) {  //��Ȩֵ˵�����˱�
			continue;  //ȥ���ظ���
		}
		this->arcs[m][n].adj = arcData->weight;
		this->arcNum++; // �߼���
	}
}

// ����������Ȩͼ 
void GraphAdjMat::CreateUDN(vector<ArcData*>* arcsList) {
	//�������ڹ�ϵ��INF|������ w|����
	//�ڽӾ���Ϊ �Գƾ���

	//��ʼ����ʱ�߶���
	ArcData* arcData = nullptr;
	// ��ʼ����ά��������
	int m = 0, n = 0;
	// ��ʼ���ߵ��ڽӾ���
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			this->arcs[i][j].adj = this->INF; // ������
		}
	}
	// �����������б�
	for (int i = 0; i < arcsList->size(); i++) {
		arcData = arcsList->at(i); // �����ȡ��
		// ��λ�ߵ����˶����λ��, mָ��n
		m = Locate(arcData->tail);
		n = Locate(arcData->head);
		// ���ö�������ΪȨ��weight��
		if (this->arcs[m][n].adj != this->INF || this->arcs[n][m].adj != this->INF) {  //��Ȩֵ˵�����˱�
			continue;  //ȥ���ظ���
		}
		if (arcData->weight == this->INF) {
			return; // ȥ��Ȩ��Ϊ����ı�
		}
		this->arcs[m][n].adj = arcData->weight;
		this->arcs[n][m].adj = arcData->weight;
		this->arcNum++; // �߼���
	}
}

// ��λ
int GraphAdjMat::Locate(string vex) {
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		if (vex == this->vexs[i]) {
			return i; // �������ַ���ʾ������Ҫ�ҵ����Ӧ������
		}
	}
	cout << endl << "����[" << vex << "]������!" << endl;
	return -1; //û�ҵ�
}

void GraphAdjMat::Display() {
	// ��ʾ��������
	cout << endl << "�������飺" << endl;
	for (int i = 0, num = 0; i < MAX_VERTEX_NUM && num < this->vexNum; i++) {
		if (vexs[i] != "") {
			cout << " (" << i << ")" << this->vexs[i];
			num++;
		}
	}
	// ��ʾ�ߣ��ڽӾ���
	cout << endl << "��(�ڽӾ���)��" << endl;
	cout << "    "; // �ĸ��ո�
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		cout << "[" << i << "]";
	}
	cout << endl;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		cout << "[" << i << "] ";
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			if (this->arcs[i][j].adj == this->INF) {
				cout << " + ";
			}
			else{
				cout << " " << this->arcs[i][j].adj << " ";
			}
		}
		cout << endl;
	}

}

// �����¶���
void GraphAdjMat::InsertVertex(string v) {
	if (Locate(v) != -1) {
		cout << endl << "�ö����Ѿ�����" << endl;
		return;
	}
	if (this->vexNum >= MAX_VERTEX_NUM) {
		cout << endl << "���������ﵽ���ޣ�" << endl;
		return;
	}
	int index = this->vexNullIndexQueue->front();  // �ӿ���������ȡ
	this->vexNullIndexQueue->pop();
	this->vexs[index] = v;
	this->vexNum++;
}

// ɾ������
void GraphAdjMat::DeleteVertex(string v) {
	int index = Locate(v);
	if (index == -1) {
		cout << endl << "���㲻����" << endl;
		return;
	}
	this->vexs[index] = "";
	this->vexNum--;
	if (this->type == DG || this->type == UDG) { // ��Ȩ
		for (int i = 0; i < MAX_VERTEX_NUM; i++) {
			this->arcs[index][i].adj = 0;
			this->arcs[i][index].adj = 0; 
		}
	}
	else{  // ��Ȩ
		for (int i = 0; i < MAX_VERTEX_NUM; i++) {
			this->arcs[index][i].adj = this->INF;
			this->arcs[i][index].adj = this->INF;
		}
	}
}

// �����
void GraphAdjMat::InsertArc(ArcData* arc) {
	int i = Locate(arc->tail);
	int j = Locate(arc->head);
	if (i == -1 || j == -1) {
		cout << endl << "�ñ߶��㲻����" << endl;
		return;
	}
	if (this->type == DG) {
		arcs[i][j].adj = 1;
	}
	else if(this->type == UDG){
		arcs[i][j].adj = 1;
		arcs[j][i].adj = 1;
	}
	else if(this->type == DN){
		arcs[i][j].adj = arc->weight;
	}
	else
	{
		arcs[i][j].adj = arc->weight;
		arcs[j][i].adj = arc->weight;
	}
	this->arcNum++;
}


// ɾ����
void GraphAdjMat::DeleteArc(ArcData* arc) {
	int i = Locate(arc->tail);
	int j = Locate(arc->head);
	if (i == -1 || j == -1) {
		cout << endl << "�ñ߶��㲻���ڣ�" << endl;
		return;
	}
	if (this->type == DG) {
		arcs[i][j].adj = 0;
	}
	else if (this->type == UDG) {
		arcs[i][j].adj = 0;
		arcs[j][i].adj = 0;
	}
	else if (this->type == DN) {
		arcs[i][j].adj = this->INF;
	}
	else
	{
		arcs[i][j].adj = this->INF;
		arcs[j][i].adj = this->INF;
	}
	this->arcNum--;
}

// ������ȱ���
void GraphAdjMat::Display_DFS(string v) {
	int index = Locate(v);
	if (index == -1) {
		return;
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		this->vexVisited[i] = 0;
	}
	cout << endl << "������ȱ���: (�Ӷ���" << v << ")��ʼ " << endl;
	DFS_R(index);
}

void GraphAdjMat::DFS_R(int index) {
	// ������ȱ��� �ݹ�
	// �����������һ����
	cout << this->vexs[index] << " ";
	this->vexVisited[index] = 1; // �ѷ���
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		//����ֵ ���� ������intֵ��0|��Ȩ  ����|��Ȩ������δ�����ʹ�ʱ���ɷ���
		if (arcs[index][i].adj != this->nonAdjInt && vexVisited[i] != 1) {
			DFS_R(i);
		}
	}
}


// ������ȱ���
void GraphAdjMat::Display_BFS(string v) {
	int index = Locate(v);
	if (index == -1) {
		return;
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		this->vexVisited[i] = 0;
	}
	cout << endl << "������ȱ���: (�Ӷ���" << v << ")��ʼ " << endl;
	queue<int> *q = new queue<int>;
	cout << this->vexs[index] << " ";
	this->vexVisited[index] = 1; // �ѷ���
	q->push(index);  // ���
	while (!q->empty()) {  // ֻҪ���зǿ�
		index = q->front();
		q->pop();
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			if (this->arcs[index][j].adj != nonAdjInt && this->vexVisited[j] != 1) {
				cout << this->vexs[j] << " "; 
				this->vexVisited[j] = 1; // ����
				q->push(j);  // ���
			}
		}
	}
	// �ͷŶ���
	while (!q->empty()) {
		q->pop();
	}
	delete q;
}



// ���Ժ���
void TestGraph() {
	vector<string>* s = new vector<string>{"v1","v2","v3","v4","v5","v6","v7"};
	GraphAdjMat::ArcData* arc1 = new GraphAdjMat::ArcData{ "v1","v2",2 };
	GraphAdjMat::ArcData* arc2 = new GraphAdjMat::ArcData{ "v1","v3",3 };
	GraphAdjMat::ArcData* arc3 = new GraphAdjMat::ArcData{ "v1","v4",4 };
	GraphAdjMat::ArcData* arc4 = new GraphAdjMat::ArcData{ "v3","v1",5 };
	GraphAdjMat::ArcData* arc5 = new GraphAdjMat::ArcData{ "v3","v2",6 };
	GraphAdjMat::ArcData* arc6 = new GraphAdjMat::ArcData{ "v3","v5",7 };
	GraphAdjMat::ArcData* arc7 = new GraphAdjMat::ArcData{ "v2","v5",8 };
	GraphAdjMat::ArcData* arc8 = new GraphAdjMat::ArcData{ "v4","v6",9 };
	GraphAdjMat::ArcData* arc9 = new GraphAdjMat::ArcData{ "v4","v7",9 };
	GraphAdjMat::ArcData* arc10 = new GraphAdjMat::ArcData{ "v6","v7",9 };


	vector<GraphAdjMat::ArcData*>* arc = new vector<GraphAdjMat::ArcData*>(); //���ڶ����Ҫ��������
	arc->push_back(arc1);
	arc->push_back(arc2);
	arc->push_back(arc3);
	arc->push_back(arc4);
	arc->push_back(arc5);
	arc->push_back(arc6);
	arc->push_back(arc7);
	arc->push_back(arc8);
	arc->push_back(arc9);
	arc->push_back(arc10);


	//����1������ͼ
	std::cout << endl << "������Ȩͼ��ʼ��" << endl;
	GraphAdjMat* udg = new GraphAdjMat(GraphAdjMat::UDG);
	udg->Init(s, arc);
	udg->Display();

	//1.1.������ȱ���
	cout << endl << "����ͼ������ȱ������У�" << endl;
	udg->Display_DFS("v1");
	cout << endl;
	//1.2.������ȱ���
	cout << endl << "����ͼ������ȱ������У�" << endl;
	udg->Display_BFS("v2");
	//1.3.�����¶��㡢�±�
	cout << endl << "����ͼ�����¶��㡢�±ߣ�" << endl;
	udg->InsertVertex("v8");
	udg->InsertArc(new GraphAdjMat::ArcData{ "v8", "v1", 8 });
	udg->Display();
	//1.4.ɾ�����㡢��
	cout << endl << "����ͼɾ������v1����arc9��" << endl;
	udg->DeleteVertex("v1");
	udg->DeleteArc(arc9);
	udg->Display();

	//����2������ͼ
	cout << endl << "������Ȩͼ��" << endl;
	GraphAdjMat* dg = new GraphAdjMat(GraphAdjMat::DG);
	dg->Init(s, arc);
	dg->Display();

	//2.1.������ȱ���
	cout << endl << "������Ȩͼ������ȱ������У�" << endl;
	dg->Display_DFS("v1");
	//2.2.������ȱ���
	cout << endl << "������Ȩͼ������ȱ������У�" << endl;
	dg->Display_BFS("v2");

	//���ԣ�������Ȩͼ(������)
	cout << endl << "������Ȩͼ��" << endl;
	GraphAdjMat* udn = new GraphAdjMat(GraphAdjMat::UDN);
	udn->Init(s, arc);
	udn->Display();

	//���ԣ�������Ȩͼ(������)
	cout << endl << "������Ȩͼ��" << endl;
	GraphAdjMat* dn = new GraphAdjMat(GraphAdjMat::DN);
	dn->Init(s, arc);
	dn->Display();


}