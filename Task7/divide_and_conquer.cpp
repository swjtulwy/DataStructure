#include"divide_and_conquer.h"

//�����Ρ�

//���÷����㷨��һ�����ݵ�����Ը���


void TestISP() {
	std::vector<int> s = { 6, 2, 1, 3, 4, 5, 1 };
	// ��ʱ�������ںϲ����裬���ڵݹ麯���п������飬��ֹ�ݹ�����ڴ���ͬʱ���ڴ�������
	std::vector<int> t(s.size()); 
	std::cout << "������������ж���Ϊ:" << InverseSequencePair(s,t,0,s.size()-1) << std::endl; 
}

int InverseSequencePair(std::vector<int>& s, std::vector<int> temp, int l, int r) {
	if (l == r) {
		return 0;
	}
	int mid = (l + r) / 2;
	int ln = InverseSequencePair(s, temp, l, mid);  // �ݹ����
	int rn = InverseSequencePair(s, temp, mid + 1, r); // �ݹ��ұ�
	int mn = Merge(s, temp, l, mid, r);  // ����һ��һ�������
	return ln + rn + mn;
}


// �߹鲢����߼���
int Merge(std::vector<int>& s, std::vector<int> temp, int l, int m, int r) {
	int count = 0;
	int k = l;  // ����������α�
	// ʹ����ʱ���� 
	for (int i = l; i <= r; i++) {
		temp[i] = s[i];
	}
	int i, j;
	for (i = l, j = m + 1; i <= m && j <= r; k++) {
		if (temp[i] > temp[j]) { // ��߷���һ�������ұߵģ���ô�������ߵ��м�Ķ���Ȼ�������ұߵĸ���
			count += m - i + 1;
			s[k] = temp[j]; // �鲢��ȡС��
			j++;
		}
		else{
			s[k] = temp[i];
			i++;
		}
	}
	if (i > m) {  
		while (j <= r) {  // �ұ߻���ʣ��
			s[k++] = temp[j++];
		}
	}
	else{
		while (i <= m) { // ��߻���ʣ��
			s[k++] = temp[i++];
		}
	}
	return count;
}