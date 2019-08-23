#include "graph_adjmat.h"
#include <iostream>
#include <vector>

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


// 求单源最短路径
void GraphAdjMat::Dijkstra(string vertex) {
	
	int start = Locate(vertex);
	if (start == -1) {
		return;
	}
	if (this->type == DG || this->type == UDG) {
		cout << "必须是加权连通图！" << endl;   // 边上要有权重，这样才能计算路径长度
		return;
	}


	//数组 D 来记录当前所找到的从源点 s 到每个顶点的最短路径长度，用数组 path 来记录到达各个顶点的前驱顶点。
	//其中，如果从源点 s 到顶点 c 有弧 ，则以弧到权值作为 D[v] 的初始值；否则将 D[v] 的初始为无穷大，path 数组初始化为 s 。

	//更新 D 的策略是，若加进 u 做中间顶点，使得 vi 的最短特殊路径长度变短，则修改 vi 的最短特殊路径长度及前驱顶点编号，即当 D[u] + W[u, vi] < D[vi] 时，令 D[vi] = D[u] + W[u, vi], path[vi] = u 。重复上述操作，一旦 S 包含了 V 中所有的顶点， D 记录了从源点 s 到各个顶点的最短路径长度，path 记录了相应最短路径的终点的前驱顶点编号。

	vector<int> dist(this->vexNum); //距离数组，每一个数组单元记录到源点的最短路径长度
	vector<string> path(this->vexNum);  // 路径数组，保存源到每个顶点的路径 用字符串表示
	for (int i = 0; i < vexNum; i++) {
		dist[i] = arcs[start][i].adj;  // 初始化最短路径距离数组
		path[i] = vertex + "-->" + vexs[i]; // 初始化为源指向顶点的字符串，例如v2-->v7
	}
	vector<int> visited(this->vexNum,0);  //状态数组，1表示已求出到当前顶点的额最短路径

	// 初始化
	dist[start] = 0;  // 源到源最短路径为0
	visited[start] = 1;

	for (int i = 1; i < vexNum; i++) { //从剩下的未求出最短路径的顶点开始依次求
		// 找一条最短的特殊路径
		int k = -1; //临时变量
		int dmin = INF;  // 寻找到当前的所有路径中路径最短的
		for (int j = 0; j < vexNum; j++) {
			if (visited[j] == 0 && dist[j] < dmin) {  // 未被访问且有源点直接到该顶点的连线
				dmin = dist[j];   // 更新当前最短路径
				k = j;  // 记录下该顶点
			}
		}
		visited[k] = 1; // 到该顶点最短路径已经求出 ,k为新加入的顶点
		// 以k为中间点，修正从start到未访问各点的距离
		for (int j = 0; j < vexNum; j++) {
			//如果 '起始点到当前点距离' + '当前点到某点距离' < '起始点到某点距离', 则更新
			if (visited[j] == 0 && dist[k]!=nonAdjInt && arcs[k][j].adj!=nonAdjInt && (dist[k] + arcs[k][j].adj) < dist[j]) {
				dist[j] = dist[k] + arcs[k][j].adj;  // 更新最短路径长度
				path[j] = path[k] + "-->" + vexs[j];  // 路径延长
			}
		}
	}
	cout << endl << "最短路径及对应长度如下:" << endl;
	for (int i = 0; i < vexNum; i++) {
		cout << path[i] <<": "<<dist[i]<< endl;
	}
}


// https://www.jianshu.com/p/3347f54a3187
// https://www.cnblogs.com/sundahua/p/7349760.html
// https://www.jianshu.com/p/62dbce1e6178
// https://www.jianshu.com/p/19ce9bc3d678
// 拓扑排序
void GraphAdjMat::Topological() {
	// 只针对有向无环图
	// 采用广度优先+队列的方法实现
	if (type==UDG || type==UDN ) {
		cout << "必须是有向图!" << endl;
		return;
	}
	vector<string> *res = new vector<string>;
	vector<int> *inDegree = new vector<int>(this->vexNum); // 入度表
	for (int i = 0; i < inDegree->size(); i++) {
		for (int j = 0; j < inDegree->size(); j++) {
			if (arcs[i][j].adj != nonAdjInt) {
				(*inDegree)[j]++;      // 计算各个结点入度
			}
		}
	}
	queue<int> *q = new queue<int>;
	for (int i = 0; i < inDegree->size(); i++) {
		if (inDegree->at(i) == 0) {
			q->push(i);
		}
	}
	while (!q->empty()) {
		int cur = q->front();
		q->pop();
		res->push_back(vexs[cur]);  // 放入结果数组
		for (int j = 0; j < inDegree->size(); j++) {
			if (arcs[cur][j].adj != nonAdjInt) {
				(*inDegree)[j]--;    // 对当前结点的任何邻接顶点的入度数减一
				if (inDegree->at(j) == 0) {
					q->push(j);   // 若有入度数为0的邻接顶点，则加入队列
				}
			}
		}
	}
	if (res->size() < inDegree->size()) {
		cout << "图中有环，不存在拓扑排序！" << endl;
		return;
	}
	cout << endl << "拓扑排序输出结果: ";
	for (int i = 0; i < res->size(); i++) {
		cout << res->at(i) << " ";
	}
	cout << endl;
}


// 判断图中是否有环
bool GraphAdjMat::HasCircle() {
	return true;
}


// 判断图是否连通
bool GraphAdjMat::IsConnected() {
	return true;

}



// 测试函数
void TestGraph() {
	//vector<string>* s = new vector<string>{"v1","v2","v3","v4","v5","v6","v7"};
	//GraphAdjMat::ArcData* arc1 = new GraphAdjMat::ArcData{ "v1","v2",2 };
	//GraphAdjMat::ArcData* arc2 = new GraphAdjMat::ArcData{ "v1","v3",3 };
	//GraphAdjMat::ArcData* arc3 = new GraphAdjMat::ArcData{ "v1","v4",4 };
	//GraphAdjMat::ArcData* arc4 = new GraphAdjMat::ArcData{ "v3","v4",5 };
	//GraphAdjMat::ArcData* arc5 = new GraphAdjMat::ArcData{ "v3","v2",6 };
	//GraphAdjMat::ArcData* arc6 = new GraphAdjMat::ArcData{ "v3","v5",7 };
	//GraphAdjMat::ArcData* arc7 = new GraphAdjMat::ArcData{ "v2","v5",8 };
	//GraphAdjMat::ArcData* arc8 = new GraphAdjMat::ArcData{ "v4","v6",9 };
	//GraphAdjMat::ArcData* arc9 = new GraphAdjMat::ArcData{ "v4","v7",9 };
	//GraphAdjMat::ArcData* arc10 = new GraphAdjMat::ArcData{ "v6","v7",9 };
	//GraphAdjMat::ArcData* arc11 = new GraphAdjMat::ArcData{ "v5","v6",6 };



	//vector<GraphAdjMat::ArcData*>* arc = new vector<GraphAdjMat::ArcData*>(); //类内定义的要加作用域
	//arc->push_back(arc1);
	//arc->push_back(arc2);
	//arc->push_back(arc3);
	//arc->push_back(arc4);
	//arc->push_back(arc5);
	//arc->push_back(arc6);
	//arc->push_back(arc7);
	//arc->push_back(arc8);
	//arc->push_back(arc9);
	//arc->push_back(arc10);
	//arc->push_back(arc11);



	////测试1：无向图
	//std::cout << endl << "无向无权图初始化" << endl;
	//GraphAdjMat* udg = new GraphAdjMat(GraphAdjMat::UDG);
	//udg->Init(s, arc);
	//udg->Display();

	////1.1.深度优先遍历
	//cout << endl << "无向图深度优先遍历序列：" << endl;
	//udg->Display_DFS("v1");
	//cout << endl;
	////1.2.广度优先遍历
	//cout << endl << "无向图广度优先遍历序列：" << endl;
	//udg->Display_BFS("v2");
	////1.3.插入新顶点、新边
	//cout << endl << "无向图插入新顶点、新边：" << endl;
	//udg->InsertVertex("v8");
	//udg->InsertArc(new GraphAdjMat::ArcData{ "v8", "v1", 8 });
	//udg->Display();
	////1.4.删除顶点、边
	//cout << endl << "无向图删除顶点v1、边arc9：" << endl;
	//udg->DeleteVertex("v1");
	//udg->DeleteArc(arc9);
	//udg->Display();

	//测试2：有向图

	vector<string>* s1 = new vector<string>{ "A","B","C","D","E" };
	GraphAdjMat::ArcData* arc1 = new GraphAdjMat::ArcData{ "A","B",3 };
	GraphAdjMat::ArcData* arc2 = new GraphAdjMat::ArcData{ "A","D",7 };
	GraphAdjMat::ArcData* arc3 = new GraphAdjMat::ArcData{ "B","D",2 };
	GraphAdjMat::ArcData* arc4 = new GraphAdjMat::ArcData{ "B","C",4 };
	GraphAdjMat::ArcData* arc5 = new GraphAdjMat::ArcData{ "D","C",5 };
	GraphAdjMat::ArcData* arc6 = new GraphAdjMat::ArcData{ "D","E",4 };
	GraphAdjMat::ArcData* arc7 = new GraphAdjMat::ArcData{ "C","E",6 };





	vector<GraphAdjMat::ArcData*>* arcs = new vector<GraphAdjMat::ArcData*>(); //类内定义的要加作用域
	arcs->push_back(arc1);
	arcs->push_back(arc2);
	arcs->push_back(arc3);
	arcs->push_back(arc4);
	arcs->push_back(arc5);
	arcs->push_back(arc6);
	arcs->push_back(arc7);



	cout << endl << "有向无权图：" << endl;
	GraphAdjMat* dg = new GraphAdjMat(GraphAdjMat::UDN);
	dg->Init(s1, arcs);
	dg->Display();

	////2.1.深度优先遍历
	//cout << endl << "有向无权图深度优先遍历序列：" << endl;
	//dg->Display_DFS("v1");
	////2.2.广度优先遍历
	//cout << endl << "有向无权图广度优先遍历序列：" << endl;
	//dg->Display_BFS("v2");
	//dg->Topological();

	dg->Dijkstra("A");
	////测试：无向有权图(无向网)
	//cout << endl << "无向有权图：" << endl;
	//GraphAdjMat* udn = new GraphAdjMat(GraphAdjMat::UDN);
	//udn->Init(s, arc);
	//udn->Display();

	////测试：有向有权图(有向网)
	//cout << endl << "有向有权图：" << endl;
	//GraphAdjMat* dn = new GraphAdjMat(GraphAdjMat::DN);
	//dn->Init(s, arc);
	//dn->Display();




}