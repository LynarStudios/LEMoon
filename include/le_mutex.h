/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Ubuntu 16.04 LTS, g++ Compiler
  date:               11.04.2018
  updated:            18.04.2018
*/

#ifndef H_LE_MUTEX
#define H_LE_MUTEX

#include <mutex>
using namespace std;

struct LEMutexFont
{
  // general

  mutex originalList;
  mutex bufferList;

  // public

  mutex fontCreateTTF;
  mutex fontDelete;
  mutex fontPrintBufferList;
  mutex fontPrintList;
  mutex fontSetStyle;
  mutex fontUsingThread;

  // locked by merge

  bool fontCreateTTFLockedByMerge;
  bool fontDeleteLockedByMerge;
};

struct LEMutexGeneral
{
  // private

  mutex printErrorDialog;

  // public
};

#endif