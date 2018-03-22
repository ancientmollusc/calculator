#include<iostream>
#include<fstream>
#include<math.h>
#include<stack>
#include<vector>
bool bracketcheck(std::stack<char> opstack)
{
	int re=0;
	while(!opstack.empty())
	{
		if(opstack.top()=='(')
		re++;
		else if(opstack.top()==')')
		re--;
		if(re<0)
		break;
		opstack.pop();
	}
	if(re==0)
	return true;
	else
	return false;
}
long double solve(long double answer,std::stack<char> &opstack,std::vector<long double> &temp,int &actni)
{
	if(opstack.top()=='(')
	{
		opstack.pop();
		answer=solve(answer,opstack,temp,actni);
		opstack.pop();
		if(!opstack.empty()&&opstack.top()!=')')
		{
		actni--;	
		answer=solve(answer,opstack,temp,actni);
	    }
		return answer;
	}
	if(!opstack.empty()&&opstack.top()=='+')
	{   
	    opstack.pop();
		if(opstack.empty())
	    {
	    	actni--;
			answer=answer+temp[actni];
			return answer;
		}
		else if(opstack.top()=='(')
		{
			actni--;
			opstack.pop();
			answer=answer+solve(temp[actni],opstack,temp,actni);
			opstack.pop();
			if(!opstack.empty()&&opstack.top()!=')')
			{
			actni--;
			answer=solve(answer,opstack,temp,actni);
			}
			return answer;
		}
		else if(opstack.top()!='('&&opstack.top()!=')')
		{
			actni--;
			answer=answer+solve(temp[actni],opstack,temp,actni);
			return answer;
		}
		else if(opstack.top()==')')
		{
			answer=answer+temp[actni-1];
			return answer;
		}
	}
	if(!opstack.empty()&&opstack.top()=='-')
	{ 
	    opstack.pop();
		if(opstack.empty())
		{
			actni--;
			answer=answer-temp[actni];
			return answer;
		}
		else if(opstack.top()=='(')
		{
			actni--;
			opstack.pop();
			answer=answer-solve(temp[actni],opstack,temp,actni);
			opstack.pop();
			if(!opstack.empty()&&opstack.top()!=')')
			{
			actni--;	
			answer=solve(answer,opstack,temp,actni);
			}
			return answer;
		}
		else if(opstack.top()!='('&&opstack.top()!=')')
		{
			actni--;
			answer=answer-solve(temp[actni],opstack,temp,actni);
		    return answer;
		}
		else if(opstack.top()==')')
		{
			answer=answer-temp[actni-1];
			return answer;
		}
	}
	if(!opstack.empty()&&opstack.top()=='*')
	{
		opstack.pop();
		if(opstack.empty())
		{
			actni--;
			answer=answer*temp[actni];
			return answer;
		}
		else if(opstack.top()=='(')
		{
			actni--;
			opstack.pop();
			answer=answer*solve(temp[actni],opstack,temp,actni);
			opstack.pop();
			if(!opstack.empty()&&opstack.top()!=')')
			{
			actni--;	
			answer=solve(answer,opstack,temp,actni);
			}
		    return answer;
	    }
	    else if(opstack.top()!='('&&opstack.top()!=')')
		{
			answer=answer*temp[actni-1];
			actni--;
			answer=solve(answer,opstack,temp,actni);
			return answer;
		}
		else if(opstack.top()==')')
		{
			answer=answer*temp[actni-1];
			return answer;
		}
	} 
	if(!opstack.empty()&&opstack.top()=='/')
	{
		opstack.pop();
		if(opstack.empty())
		{
			actni--;
			answer=answer/temp[actni];
			return answer;
		}
		else if(opstack.top()=='(')
		{
			actni--;
			opstack.pop();
			answer=answer/solve(temp[actni],opstack,temp,actni);
			opstack.pop();
			if(!opstack.empty()&&opstack.top()!=')')
			{
			actni--;	
			answer=solve(answer,opstack,temp,actni);
			}
			return answer;
	    }
	    else if(opstack.top()!='('&&opstack.top()!=')')
		{
			answer=answer/temp[actni-1];
			actni--;
			answer=solve(answer,opstack,temp,actni);
			return answer;
		}
		else if(opstack.top()==')')
		{
			answer=answer/temp[actni-1];
			return answer;
		}
	}
	if(opstack.top()==')')
	{
		return answer;
	}
	if(actni==0)
	return answer;
}
long double calculate(std::string argument)
{
	std::string openb="[{(",closeb=")}]",wobs="*/\\x^"/*without brackets solvable*/,wbs="+-"/*with brackets solvable*/,allo=wobs+wbs/*all operators*/,allb=openb+closeb/*all brackets*/;
	size_t fcs;
	int popvar=0/*check if optimazation pop has happened*/,numcount=0,decimalmult=0,errorc=0,lastc=-1/*last char type -1 start 0 num 1 ob 2 cb 3 wobs 4 wbs 5 non digit 6 bracket*/,actn=0/*active number*/;
	int actni;
	std::stack<char> calcstack/*stack for parsing, main stack*/,opstack/*stack for operations*/,dummystack;
	std::vector<long double> temp;
	temp.reserve(100);
	int duc/*dummy check*/;
	long double dup=0/*dummy to push*/,answer;
	char curchar='~',lastchar='`'/*parsing*/;
	for(int i=0;argument[i]!='\0';i++)//prepping input for parsing
	{
		calcstack.push(argument[i]);
	}
	while(!calcstack.empty())//parsing 1
	{
		if(!isdigit(calcstack.top())&&calcstack.top()!='.'&&allb.find_first_of(calcstack.top())==std::string::npos)
		{
			dummystack.push(calcstack.top());
			curchar=calcstack.top();
			if(curchar==lastchar)
			dummystack.pop();
			lastchar=curchar;
		}
		else
		{
		dummystack.push(calcstack.top());
		lastchar=calcstack.top();
	    }
		calcstack.pop();
	}
	while(!dummystack.empty())//parsing 2
	{
		calcstack.push(dummystack.top());
		dummystack.pop();
	}
	curchar='~';
	lastchar='`';
    while(!calcstack.empty())//parsing 3
    {
    	if(isdigit(calcstack.top())||calcstack.top()=='.')
    	{
    		if(lastc==-1)
			lastc=0;
    	    else if(lastc!=0)
    	    {
    	    actn++;
    	    lastc=0;
			}
			if(isdigit(calcstack.top()))
    		{	
    		duc=calcstack.top()-'0';
			temp.push_back(dup);
    		temp[actn]=temp[actn]+duc*pow(10,numcount);
    		numcount++;
    	    }
    		else if(calcstack.top()=='.')
    		{	
			decimalmult=numcount;
			errorc++;
		    }
		    lastchar=calcstack.top();
    		calcstack.pop();
    		if(calcstack.empty())
    		temp[actn]=temp[actn]/pow(10,decimalmult);
    		lastc=0;
		}
		else if(!isdigit(calcstack.top())&&!isalpha(calcstack.top()))
		{
			curchar=calcstack.top();
			if(openb.find_first_of(calcstack.top())!=std::string::npos)
			{
			curchar='(';
			opstack.push('(');
		    }
			else if(closeb.find_first_of(calcstack.top())!=std::string::npos)
			{
			curchar=')';
			opstack.push(')');
		    }
			else if(calcstack.top()=='-')
			{
				if(isdigit(lastchar))
				{
				opstack.push('+');	
				temp[actn]=-temp[actn];
			    }
			    else
			    opstack.push('-');
			}
			else
			opstack.push(calcstack.top());
			calcstack.pop();
			if(lastc!=-1)
			{
			temp[actn]=temp[actn]/pow(10,decimalmult);	
			numcount=0;
			decimalmult=0;
			errorc=0;
		    lastc=5;
			}
			if(lastchar=='+'&&curchar=='(')
			{
			opstack.pop();
		    }
		    if(curchar=='+'&&lastchar==')')
			{
			opstack.pop();
			opstack.pop();
			opstack.push(curchar);
		    }
		    if(curchar=='-'&&lastchar==')')
		    {
		    opstack.pop();
			opstack.pop();
			opstack.push(curchar);	
			}
			if(curchar=='('&&lastchar=='-'&&calcstack.empty())
			{
			opstack.pop();
			opstack.pop();
			opstack.push(curchar);	
			}
			if(curchar=='-'&&calcstack.empty())
			{
			opstack.pop();	
			}
		    if(curchar=='('&&lastchar==')')
		    {
		    opstack.pop();
		    opstack.pop();
			popvar=1;
			}
			if(lastchar=='('&&curchar==')')
		    {
		    opstack.pop();
		    opstack.pop();
			popvar=1;
			}
			if(opstack.empty()||popvar==1)
			{
			lastchar='~';
			popvar=0;
		    }
			else
			lastchar=curchar;
		}
		else
		return 0;
		if(errorc>1)
		return 0;
	}
	for(int x=0;x<=actn;x++)
	dummystack=opstack;
	while(!dummystack.empty())
	{
	dummystack.pop();
	}
	actni=actn;
	answer=temp[actni];
    if(actni>0&&bracketcheck(opstack))
    answer=solve(answer,opstack,temp,actni);
	std::vector<long double>().swap(temp);
	if(bracketcheck(opstack))
	return answer;
	else
	return 0;
}
int main(int argc, char* argv[])
{
	std::string eqstring;
        if(argc>1)
        eqstring=argv[1];
	else
        std::cin>>eqstring;
	long double ans=calculate(eqstring);
	std::cout<<ans<<'\n';
	return 0;
}
