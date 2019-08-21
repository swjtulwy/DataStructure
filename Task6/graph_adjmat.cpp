#include "graph_adjmat.h"
#include <iostream>

using namespace std;

GraphAdjMat::GraphAdjMat(int type) {
	this->type = type;
	this->vexNum = 0;
	this->arcNum = 0;
	if (this->type == DG || this->type == UDG) {
		this->nonAdjInt = 0;  //图的不相邻int值0
	}
	else{
		this->nonAdjInt = this->INF; // 网的不相邻int值无穷大
	}
}

GraphAdjMat::~GraphAdjMat() {
	// 释放顶点空位置索引队列
	while (!vexNullIndexQueue->empty()) {  // 非空
		vexNullIndexQueue->pop();
	}
	delete vexNullIndexQueue;
}

void GraphAdjMat::Init(vector<string>* vexs, vector<ArcData*>* arcLists) {
	//初始化顶点、边数据，并构建 图 | 网
	//入参：
	//vexs: 顶点 列表
	//arcsList : 边数据 列表
	
	//1.初始化顶点数据
	if (vexs->size() > MAX_VERTEX_NUM) {
		return;
	}
	for (int i = 0; i < vexs->size(); i++) {
		this->vexs[i] = vexs->at(i);
	}
	this->vexNum = vexs->size();
	//1.1初始化顶点数组空顶点位置索引队列
	// 剩下可以用的顶点索引存放到队列以备不时之需
	for (int i = vexs->size(); i < MAX_VERTEX_NUM; i++) {  
		this->vexNullIndexQueue->push(i);
	}
	//2.根据初始化类型，创建指定类型的图
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

// 创建有向无权图 
void GraphAdjMat::CreateDG(vector<ArcData*>* arcsList) {
	//顶点相邻关系：0|不相邻 1|相邻
	//邻接矩阵为 非对称矩阵

	//初始化临时边对象
	ArcData *arcData = nullptr;
	// 初始化二维矩阵坐标
	int m = 0, n = 0;
	// 初始化边的邻接矩阵
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			this->arcs[i][j].adj = 0; // 不相邻
		}
	}
	// 遍历边数据列表
	for (int i = 0; i < arcsList->size(); i++) {
		arcData = arcsList->at(i); // 按序获取边
		// 定位边的两端顶点的位置, m指向n
		m = Locate(arcData->tail);
		n = Locate(arcData->head);
		// 设置顶点相邻为1；
		if (this->arcs[m][n].adj == 1) {
			continue;  //去除重复边
		}
		this->arcs[m][n].adj = 1;
		this->arcNum++; // 边计数
	}
}

// 创建无向无权图 
void GraphAdjMat::CreateUDG(vector<ArcData*>* arcsList) {
	//顶点相邻关系：0|不相邻 1|相邻
	//邻接矩阵为 对称矩阵

	//初始化临时边对象
	ArcData* arcData = nullptr;
	// 初始化二维矩阵坐标
	int m = 0, n = 0;
	// 初始化边的邻接矩阵
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			this->arcs[i][j].adj = 0; // 不相邻
		}
	}
	// 遍历边数据列表
	for (int i = 0; i < arcsList->size(); i++) {
		arcData = arcsList->at(i); // 按序获取边
		// 定位边的两端顶点的位置, m指向n
		m = Locate(arcData->tail);
		n = Locate(arcData->head);
		// 设置顶点相邻为1；
		if (this->arcs[m][n].adj == 1 || this->arcs[n][m].adj == 1) {
			continue;  //去除重复边
		}
		this->arcs[m][n].adj = 1;
		this->arcs[n][m].adj = 1;
		this->arcNum++; // 边计数
	}
}

// 创建有向有权图 
void GraphAdjMat::CreateDN(vector<ArcData*>* arcsList) {
	//顶点相邻关系：INF|不相邻 w|相邻
	//邻接矩阵为 非对称矩阵

	//初始化临时边对象
	ArcData* arcData = nullptr;
	// 初始化二维矩阵坐标
	int m = 0, n = 0;
	// 初始化边的邻接矩阵
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			this->arcs[i][j].adj = this->INF; // 不相邻
		}
	}
	// 遍历边数据列表
	for (int i = 0; i < arcsList->size(); i++) {
		arcData = arcsList->at(i); // 按序获取边
		// 定位边的两端顶点的位置, m指向n
		m = Locate(arcData->tail);
		n = Locate(arcData->head);
		// 设置顶点相邻为权重weight；
		if (this->arcs[m][n].adj != this->INF) {  //有权值说明有了边
			continue;  //去除重复边
		}
		this->arcs[m][n].adj = arcData->weight;
		this->arcNum++; // 边计数
	}
}

// 创建无向有权图 
void GraphAdjMat::CreateUDN(vector<ArcData*>* arcsList) {
	//顶点相邻关系：INF|不相邻 w|相邻
	//邻接矩阵为 对称矩阵

	//初始化临时边对象
	ArcData* arcData = nullptr;
	// 初始化二维矩阵坐标
	int m = 0, n = 0;
	// 初始化边的邻接矩阵
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			this->arcs[i][j].adj = this->INF; // 不相邻
		}
	}
	// 遍历边数据列表
	for (int i = 0; i < arcsList->size(); i++) {
		arcData = arcsList->at(i); // 按序获取边
		// 定位边的两端顶点的位置, m指向n
		m = Locate(arcData->tail);
		n = Locate(arcData->head);
		// 设置顶点相邻为权重weight；
		if (this->arcs[m][n].adj != this->INF || this->arcs[n][m].adj != this->INF) {  //有权值说明有了边
			continue;  //去除重复边
		}
		if (arcData->weight == this->INF) {
			return; // 去除权重为无穷的边
		}
		this->arcs[m][n].adj = arcData->weight;
		this->arcs[n][m].adj = arcData->weight;
		this->arcNum++; // 边计数
	}
}

// 定位
int GraphAdjMat::Locate(string vex) {
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		if (vex == this->vexs[i]) {
			return i; // 顶点用字符表示，我们要找到其对应的索引
		}
	}
	cout << endl << "顶点[" << vex << "]不存在!" << endl;
	return -1; //没找到
}

void GraphAdjMat::Display() {
	// 显示顶点数组
	cout << endl << "顶点数组：" << endl;
	for (int i = 0, num = 0; i < MAX_VERTEX_NUM && num < this->vexNum; i++) {
		if (vexs[i] != "") {
			cout << " (" << i << ")" << this->vexs[i];
			num++;
		}
	}
	// 显示边（邻接矩阵）
	cout << endl << "边(邻接矩阵)：" << endl;
	cout << "    "; // 四个空格
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

// 插入新顶点
void GraphAdjMat::InsertVertex(string v) {
	if (Locate(v) != -1) {
		cout << endl << "该顶点已经存在" << endl;
		return;
	}
	if (this->vexNum >= MAX_VERTEX_NUM) {
		cout << endl << "顶点数量达到上限！" << endl;
		return;
	}
	int index = this->vexNullIndexQueue->front();  // 从空索引队列取
	this->vexNullIndexQueue->pop();
	this->vexs[index] = v;
	this->vexNum++;
}

// 删除顶点
void GraphAdjMat::DeleteVertex(string v) {
	int index = Locate(v);
	if (index == -1) {
		cout << endl << "顶点不存在" << endl;
		return;
	}
	this->vexs[index] = "";
	this->vexNum--;
	if (this->type == DG || this->type == UDG) { // 无权
		for (int i = 0; i < MAX_VERTEX_NUM; i++) {
			this->arcs[index][i].adj = 0;
			this->arcs[i][index].adj = 0; 
		}
	}
	else{  // 有权
		for (int i = 0; i < MAX_VERTEX_NUM; i++) {
			this->arcs[index][i].adj = this->INF;
			this->arcs[i][index].adj = this->INF;
		}
	}
}

// 插入边
void GraphAdjMat::InsertArc(ArcData* arc) {
	int i = Locate(arc->tail);
	int j = Locate(arc->head);
	if (i == -1 || j == -1) {
		cout << endl << "该边顶点不存在" << endl;
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


// 删除边
void GraphAdjMat::DeleteArc(ArcData* arc) {
	int i = Locate(arc->tail);
	int j = Locate(arc->head);
	if (i == -1 || j == -1) {
		cout << endl << "该边顶点不存在！" << endl;
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

// 深度优先遍历
void GraphAdjMat::Display_DFS(string v) {
	int index = Locate(v);
	if (index == -1) {
		return;
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		this->vexVisited[i] = 0;
	}
	cout << endl << "深度优先遍历: (从顶点" << v << ")开始 " << endl;
	DFS_R(index);
}

void GraphAdjMat::DFS_R(int index) {
	// 深度优先遍历 递归
	// 有向和无向是一样的
	cout << this->vexs[index] << " ";
	this->vexVisited[index] = 1; // 已访问
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		//当边值 不是 不相邻int值（0|无权  无穷|有权），且未被访问过时，可访问
		if (arcs[index][i].adj != this->nonAdjInt && vexVisited[i] != 1) {
			DFS_R(i);
		}
	}
}


// 广度优先遍历
void GraphAdjMat::Display_BFS(string v) {
	int index = Locate(v);
	if (index == -1) {
		return;
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		this->vexVisited[i] = 0;
	}
	cout << endl << "广度优先遍历: (从顶点" << v << ")开始 " << endl;
	queue<int> *q = new queue<int>;
	cout << this->vexs[index] << " ";
	this->vexVisited[index] = 1; // 已访问
	q->push(index);  // 入队
	while (!q->empty()) {  // 只要队列非空
		index = q->front();
		q->pop();
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			if (this->arcs[index][j].adj != nonAdjInt && this->vexVisited[j] != 1) {
				cout << this->vexs[j] << " "; 
				this->vexVisited[j] = 1; // 访问
				q->push(j);  // 入队
			}
		}
	}
	// 释放队列
	while (!q->empty()) {
		q->pop();
	}
	delete q;
}



// 测试函数
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


	vector<GraphAdjMat::ArcData*>* arc = new vector<GraphAdjMat::ArcData*>(); //类内定义的要加作用域
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


	//测试1：无向图
	std::cout << endl << "无向无权图初始化" << endl;
	GraphAdjMat* udg = new GraphAdjMat(GraphAdjMat::UDG);
	udg->Init(s, arc);
	udg->Display();

	//1.1.深度优先遍历
	cout << endl << "无向图深度优先遍历序列：" << endl;
	udg->Display_DFS("v1");
	cout << endl;
	//1.2.广度优先遍历
	cout << endl << "无向图广度优先遍历序列：" << endl;
	udg->Display_BFS("v2");
	//1.3.插入新顶点、新边
	cout << endl << "无向图插入新顶点、新边：" << endl;
	udg->InsertVertex("v8");
	udg->InsertArc(new GraphAdjMat::ArcData{ "v8", "v1", 8 });
	udg->Display();
	//1.4.删除顶点、边
	cout << endl << "无向图删除顶点v1、边arc9：" << endl;
	udg->DeleteVertex("v1");
	udg->DeleteArc(arc9);
	udg->Display();

	//测试2：有向图
	cout << endl << "有向无权图：" << endl;
	GraphAdjMat* dg = new GraphAdjMat(GraphAdjMat::DG);
	dg->Init(s, arc);
	dg->Display();

	//2.1.深度优先遍历
	cout << endl << "有向无权图深度优先遍历序列：" << endl;
	dg->Display_DFS("v1");
	//2.2.广度优先遍历
	cout << endl << "有向无权图广度优先遍历序列：" << endl;
	dg->Display_BFS("v2");

	//测试：无向有权图(无向网)
	cout << endl << "无向有权图：" << endl;
	GraphAdjMat* udn = new GraphAdjMat(GraphAdjMat::UDN);
	udn->Init(s, arc);
	udn->Display();

	//测试：有向有权图(有向网)
	cout << endl << "有向有权图：" << endl;
	GraphAdjMat* dn = new GraphAdjMat(GraphAdjMat::DN);
	dn->Init(s, arc);
	dn->Display();


}