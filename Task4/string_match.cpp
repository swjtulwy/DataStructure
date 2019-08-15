#include "string_match.h"

void TestStringMatch() {
	string t = {"nijiushigedashabi"}; // 17
	string p = { "bi" }; // 2
	int res = StringMatch::NavieMatch(t, p);
	if (res == -1) {
		cout << "match fail!"<<endl;
	}
	else{
		cout << "matched at: ";
		cout << "[" << res << "," << res + p.length() - 1 << "]" << endl;
	}
}
// �����ַ���ƥ��Ҳ����������ƥ��
int StringMatch::NavieMatch(string text, string pattern) {
	int n = text.length();  // Ŀ�괮����
	int m = pattern.length();  // ģʽ����
	// ����
	for (int i = 0; i < n - m + 1; i++) {
		int j = 0;
		while (j < m) {
			if (pattern[j] == text[i + j]) {
				j++;
			}
			else{
				break;
			}
		}
		if (j == m) {
			return i;
		}
	}
	return -1;
}