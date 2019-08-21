#pragma once
#include<string>
#include <limits>
#include<queue>
#include <vector>


using namespace std;

void TestGraph();

// 邻接矩阵每一个单元可表示一条边的信息
class GraphAdjMat {
	struct ArcCell    // 存储边信息的结构体
	{
		int adj;   // 邻接顶点关系。图：0|不相邻 1|相邻 ；网(带权图)：无穷（INT_MAX）|不相邻  权值（W）|相邻
		string info;   // 边（弧）信息
	};
public:
	struct ArcData         // 便于输入的一个结构体
	{
		string tail;   // 弧尾
		string head;   // 弧头
		int weight;    // 权重
	};
	enum Graphtype
	{
		DG,        // 有向无权图
		UDG,	   // 无向无权图
		DN,		   // 有向有权图(有向网)
		UDN        // 无向有权图(无向网)
	};

private:
	const int INF = INT_MAX;   // 无穷大
	static const int MAX_VERTEX_NUM = 10;  //支持的最多顶点数

	// 静态存储结构
	string vexs[MAX_VERTEX_NUM];    // 顶点表
	ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   // 边矩阵
	int vexNum;          // 顶点数
	int arcNum;          // 边数
	int type;            // 图种类
	int nonAdjInt;      // 不相邻int值：0无权| 无穷|有权
	
	queue<int>* vexNullIndexQueue = new queue<int>; //顶点数组中空顶点位置索引队列 （需要销毁）
	bool vexVisited[MAX_VERTEX_NUM];  //顶点访问标记数组：0|未访问 1|已访问

	void CreateDG(vector<ArcData*>* arcsList);
	void CreateUDG(vector<ArcData*>* arcsList);
	void CreateDN(vector<ArcData*>* arcsList);
	void CreateUDN(vector<ArcData*>* arcsList);

	int Locate(string vex);  // 定位顶点元素位置
	void DFS_R(int vex);  // 递归深度优先遍历

public:
	GraphAdjMat(int type);  // 构造函数：初始化图类型
	~GraphAdjMat();
	
	void Init(vector<string>* vexs, vector<ArcData*>* arcLists); // 初始化顶点、边数据
	void Display();
	void InsertVertex(string v);   // 插入顶点
	void DeleteVertex(string v);   // 删除顶点
	void InsertArc(ArcData* arc);  // 插入边
	void DeleteArc(ArcData* arc);  // 删除边
	void Display_DFS(string v);   // 从指定顶点开始深度优先遍历
	void Display_BFS(string v);   // 从指定顶点开始广度优先遍历


	GraphAdjMat* MiniSpanTree_Prim(string vertex);		//最小生成树（Prim 算法）
	GraphAdjMat* MiniSpanTree_Kruskal(string vertex);	//最小生成树（Kruskal 算法）

};
