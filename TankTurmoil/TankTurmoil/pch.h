// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。
#pragma once

#ifndef PCH_H
#define PCH_H

#include "framework.h"

#endif //PCH_H

// 添加要在此处预编译的标头
#include <cassert>
#include <cmath>
#include <algorithm>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <stack>
#include <string>
#include <strstream>
#include <tuple>
#include <vector>

using namespace std;

#include <gdiplus.h>				//包含
#pragma comment(lib, "Gdiplus.lib")	//链接
using namespace Gdiplus;			// 使用Gdiplus命名空间

#define PI 3.14159265357f

struct PathNode {
    int x;
    int y;
};

typedef std::vector<PathNode> VPath;

// 删除内存的宏 
#define SAFE_DEL_PTR(ptr) if((ptr) != nullptr){delete ptr;ptr= nullptr;}


