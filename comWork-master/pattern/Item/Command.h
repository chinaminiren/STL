//将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化；对请求排队或记录请求日志，以及支持可撤销的操作。
//“行为请求者”与“行为实现者”通常呈现一种“紧耦合”的问题。 
/*
  (1) 降低系统的耦合度。由于请求者与接收者之间不存在直接引用，因此请求者与接收者之间实现完全解耦，相同的请求者可以对应不同的接收者，同样，相同的接收者也可以供不同的请求者使用，两者之间具有良好的独立性。
  (2) 新的命令可以很容易地加入到系统中。由于增加新的具体命令类不会影响到其他类，因此增加新的具体命令类很容易，无须修改原有系统源代码，甚至客户类代码，满足“开闭原则”的要求。
  (3) 可以比较容易地设计一个命令队列或宏命令（组合命令）。
  (4) 为请求的撤销(Undo)和恢复(Redo)操作提供了一种设计和实现方案。
  缺点：使用命令模式可能会导致某些系统有过多的具体命令类
*/
//一个命令对象和请求的初始调用者可以有不同的生命期

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class ICommand
{
public:
	virtual void Exec(void*)=0;
	virtual void ReDo()=0;
	virtual void Cancel()=0;
	virtual ~ICommand(){};
};

class ReciveFile
{
   //OpenFileCommand 真正的执行者
};
class ReciveImage
{
	//ImageCommand 真正的业务执行者
};

class OpenFileCommand:public ICommand
{
public:
	OpenFileCommand(ReciveFile* ptr):recive(ptr)
	{

	}
	virtual void Exec(void* obj)
	{

	}
	virtual void ReDo()
	{

	}
	virtual void Cancel()
	{

	}
private:
	tr1::shared_ptr<ReciveFile> recive;
};
class OpenImageCommand:public ICommand
{
public:
	OpenImageCommand(ReciveImage* ptr):recive(ptr)
	{

	}
	virtual void Exec(void* obj)
	{

	}
	virtual void ReDo()
	{

	}
	virtual void Cancel()
	{

	}
private:
	tr1::shared_ptr<ReciveImage> recive;
};
class CommandManage
{
public:
	void AddCommand(ICommand* cmd)
	{
		this->commandlist.push_back(cmd);
	}
	void ExecCommand()
	{
		//或者执行命令队列
		//或者根据参数执行哪一个 命令
		//记录日志
	}
private:
	vector<ICommand*> commandlist;
};

void TestCommand()
{
	ICommand* filecommand=new OpenFileCommand(new ReciveFile());
	ICommand* imagecommand=new OpenImageCommand(new ReciveImage());

	CommandManage cmage;
	cmage.AddCommand(filecommand);
	cmage.AddCommand(imagecommand);

	delete imagecommand;
	delete filecommand;
}


