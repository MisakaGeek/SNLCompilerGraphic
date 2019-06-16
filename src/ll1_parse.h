#ifndef LL1_PARSE_H
#define LL1_PARSE_H

#include "globals.h"

#include <QObject>
#include <QSharedPointer>
#include <QStack>
#include <QThread>



extern QSet<LexType> NTSet;
extern QSet<LexType> TTSet;

extern int lineno;
extern QMap<LexType, QString> lexName;
class LL1_parse :public QThread
{
	Q_OBJECT
public:

	static LL1_parse *getInstance(const Token *head) {
		auto instance = new LL1_parse(head);
		return instance;
	}
	TreeNode *get_parsetree_head();
	// QThread interface
protected:
	void run() override;

signals:
	void parse_success(QSharedPointer<TreeNode> p, QString title);


private:
	LL1_parse(const Token *root);
	void createLL1Table();
	void process(int id);
private:
	//ָ��Token���к�line
	const Token *head;
	//Ԥ�������
	QMap<QPair<LexType, LexType>, int> table;
	//����ջ �����Token���ֱ���
	QStack<LexType> symbal_stack;
	//�﷨�������ڵ�ջ
	QStack<TreeNode **> syntaxtree_stack;
	//������ջ
	QStack<TreeNode *> op_stack;
	//������ջ
	QStack<TreeNode *> num_stack;
	//�﷨�������ĸ��ڵ�
	TreeNode *root;
};

#endif // LL1_PARSE_H
