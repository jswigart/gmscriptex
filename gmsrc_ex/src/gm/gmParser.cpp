
/*  A Bison parser, made from gmparser.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse gmparse
#define yylex gmlex
#define yyerror gmerror
#define yylval gmlval
#define yychar gmchar
#define yydebug gmdebug
#define yynerrs gmnerrs
#define	KEYWORD_LOCAL	258
#define	KEYWORD_GLOBAL	259
#define	KEYWORD_MEMBER	260
#define	KEYWORD_AND	261
#define	KEYWORD_OR	262
#define	KEYWORD_IF	263
#define	KEYWORD_ELSE	264
#define	KEYWORD_WHILE	265
#define	KEYWORD_FOR	266
#define	KEYWORD_FOREACH	267
#define	KEYWORD_IN	268
#define	KEYWORD_BREAK	269
#define	KEYWORD_CONTINUE	270
#define	KEYWORD_NULL	271
#define	KEYWORD_DOWHILE	272
#define	KEYWORD_RETURN	273
#define	KEYWORD_FUNCTION	274
#define	KEYWORD_TABLE	275
#define	KEYWORD_THIS	276
#define	KEYWORD_TRUE	277
#define	KEYWORD_FALSE	278
#define	KEYWORD_FORK	279
#define	KEYWORD_SWITCH	280
#define	KEYWORD_CASE	281
#define	KEYWORD_DEFAULT	282
#define	IDENTIFIER	283
#define	CONSTANT_HEX	284
#define	CONSTANT_BINARY	285
#define	CONSTANT_INT	286
#define	CONSTANT_CHAR	287
#define	CONSTANT_FLOAT	288
#define	CONSTANT_STRING	289
#define	SYMBOL_ASGN_BSR	290
#define	SYMBOL_ASGN_BSL	291
#define	SYMBOL_ASGN_ADD	292
#define	SYMBOL_ASGN_MINUS	293
#define	SYMBOL_ASGN_TIMES	294
#define	SYMBOL_ASGN_DIVIDE	295
#define	SYMBOL_ASGN_REM	296
#define	SYMBOL_ASGN_BAND	297
#define	SYMBOL_ASGN_BOR	298
#define	SYMBOL_ASGN_BXOR	299
#define	SYMBOL_RIGHT_SHIFT	300
#define	SYMBOL_LEFT_SHIFT	301
#define	SYMBOL_INC	302
#define	SYMBOL_DEC	303
#define	SYMBOL_LTE	304
#define	SYMBOL_GTE	305
#define	SYMBOL_EQ	306
#define	SYMBOL_NEQ	307
#define	TOKEN_ERROR	308

#line 12 "gmparser.y"


#define YYPARSER
#include "gmConfig.h"
#include "gmCodeTree.h"
#define YYSTYPE gmCodeTreeNode *

extern gmCodeTreeNode * g_codeTree;

#define GM_BISON_DEBUG
#ifdef GM_BISON_DEBUG
#define YYDEBUG 1
#define YYERROR_VERBOSE
#endif // GM_BISON_DEBUG

//
// HELPERS
//

void ATTACH(gmCodeTreeNode * &a_res, gmCodeTreeNode * a_a, gmCodeTreeNode * a_b)
{
  YYSTYPE t = a_a;
  if(t != NULL)
  {
    while(t->m_sibling != NULL)
    {
      t = t->m_sibling;
    }
    t->m_sibling = a_b;
    if(a_b) { a_b->m_parent = t; }
    a_res = a_a;
  }
  else
  {
    a_res = a_b;
  }
}

gmCodeTreeNode * CreateOperation(int a_subTypeType, gmCodeTreeNode * a_left = NULL, gmCodeTreeNode * a_right = NULL)
{
  gmCodeTreeNode * node = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_OPERATION, gmlineno, a_subTypeType);
  node->SetChild(0, a_left);
  node->SetChild(1, a_right);
  return node;
}

gmCodeTreeNode * CreateAsignExpression(int a_subTypeType, gmCodeTreeNode * a_left, gmCodeTreeNode * a_right)
{
  // we need to evaluate the complexety of the l-value... if it is a function call, index or dot to the left of a dot or index, we need to cache
  // into a hidden variable.

  // todo

  gmCodeTreeNode * opNode = CreateOperation(a_subTypeType, a_left, a_right);
  return CreateOperation(CTNOT_ASSIGN, a_left, opNode);
}


#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		269
#define	YYFLAG		-32768
#define	YYNTBASE	77

#define YYTRANSLATE(x) ((unsigned)(x) <= 308 ? yytranslate[x] : 119)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    75,     2,     2,     2,    73,    66,     2,    58,
    59,    71,    69,    76,    70,    63,    72,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    60,    56,    67,
    57,    68,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    61,     2,    62,    65,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    54,    64,    55,    74,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,     7,     9,    11,    13,    15,    17,    20,
    24,    28,    34,    36,    38,    40,    42,    45,    51,    59,
    67,    71,    74,    82,    86,    91,    95,    97,   100,   102,
   107,   111,   113,   116,   118,   120,   126,   132,   139,   147,
   155,   165,   168,   171,   174,   178,   180,   184,   188,   192,
   196,   200,   204,   208,   212,   216,   220,   224,   226,   229,
   231,   233,   237,   239,   243,   245,   249,   251,   255,   257,
   261,   263,   267,   271,   273,   277,   281,   285,   289,   291,
   295,   299,   301,   305,   309,   311,   315,   319,   323,   325,
   328,   331,   334,   336,   338,   340,   342,   344,   349,   353,
   358,   364,   371,   375,   377,   381,   385,   390,   393,   397,
   402,   408,   413,   415,   419,   421,   425,   431,   433,   435,
   439,   441,   445,   447,   450,   452,   454,   456,   458,   462,
   464,   466,   468,   470,   472,   474,   476,   478,   480,   482,
   484
};

static const short yyrhs[] = {    78,
     0,    79,     0,    78,    79,     0,    83,     0,    81,     0,
    84,     0,    89,     0,    90,     0,    54,    55,     0,    54,
    78,    55,     0,    82,   116,    56,     0,    82,   116,    57,
    93,    56,     0,     3,     0,     4,     0,     5,     0,    56,
     0,    91,    56,     0,     8,    58,    93,    59,    80,     0,
     8,    58,    93,    59,    80,     9,    80,     0,     8,    58,
    93,    59,    80,     9,    84,     0,    24,   116,    80,     0,
    24,    80,     0,    25,    58,    93,    59,    54,    86,    55,
     0,    26,    87,    60,     0,    26,    87,    60,    80,     0,
    27,    60,    80,     0,    85,     0,    86,    85,     0,    88,
     0,    87,    61,    93,    62,     0,    87,    63,   116,     0,
   116,     0,    63,   116,     0,    21,     0,   117,     0,    10,
    58,    93,    59,    80,     0,    17,    58,    93,    59,    80,
     0,    11,    58,    83,    92,    59,    80,     0,    11,    58,
    83,    92,    91,    59,    80,     0,    12,    58,   116,    13,
    93,    59,    80,     0,    12,    58,   116,     6,   116,    13,
    93,    59,    80,     0,    15,    56,     0,    14,    56,     0,
    18,    56,     0,    18,    93,    56,     0,    94,     0,   106,
    57,    94,     0,   106,    35,    94,     0,   106,    36,    94,
     0,   106,    37,    94,     0,   106,    38,    94,     0,   106,
    39,    94,     0,   106,    40,    94,     0,   106,    41,    94,
     0,   106,    42,    94,     0,   106,    43,    94,     0,   106,
    44,    94,     0,    56,     0,    93,    56,     0,    94,     0,
    95,     0,    94,     7,    95,     0,    96,     0,    95,     6,
    96,     0,    97,     0,    96,    64,    97,     0,    98,     0,
    97,    65,    98,     0,    99,     0,    98,    66,    99,     0,
   100,     0,    99,    51,   100,     0,    99,    52,   100,     0,
   101,     0,   100,    67,   101,     0,   100,    68,   101,     0,
   100,    49,   101,     0,   100,    50,   101,     0,   102,     0,
   101,    46,   102,     0,   101,    45,   102,     0,   103,     0,
   102,    69,   103,     0,   102,    70,   103,     0,   104,     0,
   103,    71,   104,     0,   103,    72,   104,     0,   103,    73,
   104,     0,   106,     0,    47,   104,     0,    48,   104,     0,
   105,   104,     0,    69,     0,    70,     0,    74,     0,    75,
     0,   115,     0,   106,    61,    93,    62,     0,   106,    58,
    59,     0,   106,    58,   107,    59,     0,   106,    60,   116,
    58,    59,     0,   106,    60,   116,    58,   107,    59,     0,
   106,    63,   116,     0,    93,     0,   107,    76,    93,     0,
    20,    58,    59,     0,    20,    58,   110,    59,     0,    54,
    55,     0,    54,   110,    55,     0,    54,   110,    76,    55,
     0,    19,    58,   113,    59,    80,     0,    19,    58,    59,
    80,     0,   111,     0,   110,    76,   111,     0,    93,     0,
   116,    57,    93,     0,    61,   112,    62,    57,    93,     0,
    31,     0,   114,     0,   113,    76,   114,     0,   116,     0,
   116,    57,    93,     0,   116,     0,    63,   116,     0,    21,
     0,   117,     0,   108,     0,   109,     0,    58,    93,    59,
     0,    28,     0,    29,     0,    30,     0,    31,     0,    22,
     0,    23,     0,    32,     0,    33,     0,   118,     0,    16,
     0,    34,     0,   118,    34,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   128,   135,   139,   146,   150,   154,   158,   162,   169,   173,
   181,   186,   195,   199,   203,   209,   213,   220,   226,   233,
   240,   246,   251,   260,   266,   273,   281,   285,   292,   296,
   300,   307,   311,   316,   320,   329,   335,   341,   348,   356,
   363,   374,   378,   382,   386,   394,   402,   406,   410,   414,
   418,   422,   426,   430,   434,   438,   442,   450,   454,   461,
   468,   472,   479,   483,   490,   494,   502,   506,   514,   518,
   526,   530,   534,   541,   545,   549,   553,   557,   564,   568,
   573,   581,   585,   590,   598,   602,   607,   612,   620,   624,
   628,   632,   641,   645,   649,   653,   660,   664,   668,   673,
   679,   685,   692,   699,   703,   710,   714,   719,   723,   728,
   736,   742,   750,   754,   761,   765,   769,   776,   785,   789,
   796,   801,   810,   814,   819,   823,   827,   831,   835,   842,
   851,   856,   861,   866,   871,   876,   922,   927,   931,   939,
   953
};

static const char * const yytname[] = {   "$","error","$undefined.","KEYWORD_LOCAL",
"KEYWORD_GLOBAL","KEYWORD_MEMBER","KEYWORD_AND","KEYWORD_OR","KEYWORD_IF","KEYWORD_ELSE",
"KEYWORD_WHILE","KEYWORD_FOR","KEYWORD_FOREACH","KEYWORD_IN","KEYWORD_BREAK",
"KEYWORD_CONTINUE","KEYWORD_NULL","KEYWORD_DOWHILE","KEYWORD_RETURN","KEYWORD_FUNCTION",
"KEYWORD_TABLE","KEYWORD_THIS","KEYWORD_TRUE","KEYWORD_FALSE","KEYWORD_FORK",
"KEYWORD_SWITCH","KEYWORD_CASE","KEYWORD_DEFAULT","IDENTIFIER","CONSTANT_HEX",
"CONSTANT_BINARY","CONSTANT_INT","CONSTANT_CHAR","CONSTANT_FLOAT","CONSTANT_STRING",
"SYMBOL_ASGN_BSR","SYMBOL_ASGN_BSL","SYMBOL_ASGN_ADD","SYMBOL_ASGN_MINUS","SYMBOL_ASGN_TIMES",
"SYMBOL_ASGN_DIVIDE","SYMBOL_ASGN_REM","SYMBOL_ASGN_BAND","SYMBOL_ASGN_BOR",
"SYMBOL_ASGN_BXOR","SYMBOL_RIGHT_SHIFT","SYMBOL_LEFT_SHIFT","SYMBOL_INC","SYMBOL_DEC",
"SYMBOL_LTE","SYMBOL_GTE","SYMBOL_EQ","SYMBOL_NEQ","TOKEN_ERROR","'{'","'}'",
"';'","'='","'('","')'","':'","'['","']'","'.'","'|'","'^'","'&'","'<'","'>'",
"'+'","'-'","'*'","'/'","'%'","'~'","'!'","','","program","statement_list","statement",
"compound_statement","var_statement","var_type","expression_statement","selection_statement",
"case_selection_statement","case_selection_statement_list","postfix_case_expression",
"case_expression","iteration_statement","jump_statement","assignment_expression",
"constant_expression_statement","constant_expression","logical_or_expression",
"logical_and_expression","inclusive_or_expression","exclusive_or_expression",
"and_expression","equality_expression","relational_expression","shift_expression",
"additive_expression","multiplicative_expression","unary_expression","unary_operator",
"postfix_expression","argument_expression_list","table_constructor","function_constructor",
"field_list","field","constant_field_index","parameter_list","parameter","primary_expression",
"identifier","constant","constant_string_list",""
};
#endif

static const short yyr1[] = {     0,
    77,    78,    78,    79,    79,    79,    79,    79,    80,    80,
    81,    81,    82,    82,    82,    83,    83,    84,    84,    84,
    84,    84,    84,    85,    85,    85,    86,    86,    87,    87,
    87,    88,    88,    88,    88,    89,    89,    89,    89,    89,
    89,    90,    90,    90,    90,    91,    91,    91,    91,    91,
    91,    91,    91,    91,    91,    91,    91,    92,    92,    93,
    94,    94,    95,    95,    96,    96,    97,    97,    98,    98,
    99,    99,    99,   100,   100,   100,   100,   100,   101,   101,
   101,   102,   102,   102,   103,   103,   103,   103,   104,   104,
   104,   104,   105,   105,   105,   105,   106,   106,   106,   106,
   106,   106,   106,   107,   107,   108,   108,   108,   108,   108,
   109,   109,   110,   110,   111,   111,   111,   112,   113,   113,
   114,   114,   115,   115,   115,   115,   115,   115,   115,   116,
   117,   117,   117,   117,   117,   117,   117,   117,   117,   118,
   118
};

static const short yyr2[] = {     0,
     1,     1,     2,     1,     1,     1,     1,     1,     2,     3,
     3,     5,     1,     1,     1,     1,     2,     5,     7,     7,
     3,     2,     7,     3,     4,     3,     1,     2,     1,     4,
     3,     1,     2,     1,     1,     5,     5,     6,     7,     7,
     9,     2,     2,     2,     3,     1,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     1,     2,     1,
     1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
     1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
     3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
     2,     2,     1,     1,     1,     1,     1,     4,     3,     4,
     5,     6,     3,     1,     3,     3,     4,     2,     3,     4,
     5,     4,     1,     3,     1,     3,     5,     1,     1,     3,
     1,     3,     1,     2,     1,     1,     1,     1,     3,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     2
};

static const short yydefact[] = {     0,
    13,    14,    15,     0,     0,     0,     0,     0,     0,   139,
     0,     0,     0,     0,   125,   134,   135,     0,     0,   130,
   131,   132,   133,   136,   137,   140,     0,     0,     0,    16,
     0,     0,    93,    94,    95,    96,     1,     2,     5,     0,
     4,     6,     7,     8,     0,    46,    61,    63,    65,    67,
    69,    71,    74,    79,    82,    85,     0,    89,   127,   128,
    97,   123,   126,   138,     0,     0,     0,     0,    43,    42,
     0,    44,     0,    60,    89,     0,     0,     0,    22,     0,
     0,    90,    91,   108,     0,   115,     0,   113,   123,     0,
   124,     3,     0,    17,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    92,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   141,     0,
     0,     0,     0,     0,    45,     0,     0,   119,   121,   106,
     0,     9,     0,    21,     0,   118,     0,   109,     0,     0,
   129,    11,     0,    62,    64,    66,    68,    70,    72,    73,
    77,    78,    75,    76,    81,    80,    83,    84,    86,    87,
    88,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    47,    99,   104,     0,     0,     0,   103,     0,     0,
    58,     0,     0,     0,     0,     0,   112,     0,     0,     0,
   107,     0,    10,     0,     0,   110,   114,   116,     0,   100,
     0,     0,    98,    18,    36,     0,     0,    59,     0,     0,
    37,   111,   120,   122,     0,     0,    12,   105,   101,     0,
     0,    38,     0,     0,     0,     0,     0,    27,     0,   117,
   102,    19,    20,    39,     0,    40,    34,     0,     0,    29,
    32,    35,     0,    23,    28,     0,    33,    24,     0,     0,
    26,    41,    25,     0,    31,    30,     0,     0,     0
};

static const short yydefgoto[] = {   267,
    37,    38,    79,    39,    40,    41,    42,   238,   239,   249,
   250,    43,    44,    45,   192,    86,    74,    47,    48,    49,
    50,    51,    52,    53,    54,    55,    56,    57,    75,   185,
    59,    60,    87,    88,   147,   137,   138,    61,    62,    63,
    64
};

static const short yypact[] = {   382,
-32768,-32768,-32768,   -30,   -26,     8,    20,   -15,    36,-32768,
    37,   610,    38,    39,-32768,-32768,-32768,   -17,    42,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,  1009,  1009,   439,-32768,
  1009,    18,-32768,-32768,-32768,-32768,   382,-32768,-32768,    18,
-32768,-32768,-32768,-32768,    45,    61,    96,    40,    41,    43,
    -3,   -16,   -28,   -14,    12,-32768,  1009,   124,-32768,-32768,
-32768,-32768,-32768,    69,  1009,  1009,   667,    18,-32768,-32768,
  1009,-32768,    49,    61,     4,   -20,   496,   246,-32768,    53,
  1009,-32768,-32768,-32768,    81,-32768,   -46,-32768,    57,    59,
-32768,-32768,    30,-32768,  1009,  1009,  1009,  1009,  1009,  1009,
  1009,  1009,  1009,  1009,  1009,  1009,  1009,  1009,  1009,  1009,
  1009,  1009,-32768,  1009,  1009,  1009,  1009,  1009,  1009,  1009,
  1009,  1009,  1009,  1009,   724,    18,  1009,    18,-32768,    63,
    76,   781,    32,    77,-32768,    53,   -47,-32768,    82,-32768,
   -45,-32768,   314,-32768,    83,-32768,    54,-32768,   553,  1009,
-32768,-32768,  1009,    96,    40,    41,    43,    -3,   -16,   -16,
   -28,   -28,   -28,   -28,   -14,   -14,    12,    12,-32768,-32768,
-32768,    61,    61,    61,    61,    61,    61,    61,    61,    61,
    61,    61,-32768,-32768,   -34,    85,    78,-32768,    53,    53,
-32768,   838,    89,    18,  1009,    53,-32768,    53,    18,  1009,
-32768,   895,-32768,    93,    91,-32768,-32768,-32768,    94,-32768,
  1009,   952,-32768,   140,-32768,    53,    92,-32768,   142,    98,
-32768,-32768,-32768,-32768,    34,  1009,-32768,-32768,-32768,   -33,
    -4,-32768,    53,  1009,    53,   196,   109,-32768,   -11,-32768,
-32768,-32768,-32768,-32768,    99,-32768,-32768,    18,    19,-32768,
-32768,-32768,    53,-32768,-32768,    53,-32768,    53,  1009,    18,
-32768,-32768,-32768,   108,-32768,-32768,   171,   172,-32768
};

static const short yypgoto[] = {-32768,
    95,   -35,   -79,-32768,-32768,   111,   -56,   -63,-32768,-32768,
-32768,-32768,-32768,    -6,-32768,   -12,    10,    97,    84,   101,
   103,   104,   -78,   -29,   -13,   -10,   -21,-32768,     3,   -22,
-32768,-32768,   114,  -144,-32768,-32768,     5,-32768,    -5,   -43,
-32768
};


#define	YYLAST		1084


static const short yytable[] = {    73,
   144,    92,    58,     4,   207,    82,    83,    20,   148,    46,
    20,   198,    80,   201,   236,   237,   106,   107,    90,    18,
    19,   159,   160,    89,   210,   241,    91,    65,   199,   149,
   202,    66,   102,   103,    93,   113,    78,   194,   136,    58,
    69,   211,   211,   254,   195,    20,    46,   100,   101,    78,
   104,   105,   130,   131,   108,   109,   197,   207,   134,   236,
   237,   125,   133,   126,   127,    67,   128,    95,   145,    58,
   139,    89,   161,   162,   163,   164,    46,    68,   258,   259,
    58,   260,   110,   111,   112,   152,   153,    46,   169,   170,
   171,    70,   165,   166,    71,    76,    77,   167,   168,    81,
    94,    96,   129,    97,   135,    98,    78,    92,    99,   214,
   215,   146,   184,   150,   187,   205,   221,   151,   222,   193,
   186,   189,   188,   172,   173,   174,   175,   176,   177,   178,
   179,   180,   181,   182,   190,   196,   232,   208,   200,   213,
   209,   204,   212,    89,   218,    58,   225,   226,   231,   227,
   233,   242,    46,   244,   234,   246,   235,   256,   114,   115,
   116,   117,   118,   119,   120,   121,   122,   123,   253,   266,
   268,   269,   143,   261,   243,   255,   262,   132,   263,   155,
   124,   125,   220,   126,   127,   217,   128,   224,   219,   230,
   141,   154,   252,   139,    58,     0,    89,   156,   228,   184,
   157,    46,   158,   223,     0,     0,     0,     0,     0,     0,
     0,    10,     0,   240,     0,     0,   247,    16,    17,     0,
     0,   245,     0,    20,    21,    22,    23,    24,    25,    26,
   251,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   257,     0,     0,     0,   264,     0,     1,     2,
     3,     0,     0,     4,   265,     5,     6,     7,   248,     8,
     9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
    19,     0,     0,    20,    21,    22,    23,    24,    25,    26,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    27,    28,     0,     0,     0,     0,     0,    29,
   142,    30,     0,    31,     0,     0,     0,     0,    32,     0,
     0,     0,     0,     0,    33,    34,     1,     2,     3,    35,
    36,     4,     0,     5,     6,     7,     0,     8,     9,    10,
    11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
     0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    27,    28,     0,     0,     0,     0,     0,    29,   203,    30,
     0,    31,     0,     0,     0,     0,    32,     0,     0,     0,
     0,     0,    33,    34,     1,     2,     3,    35,    36,     4,
     0,     5,     6,     7,     0,     8,     9,    10,    11,    12,
    13,    14,    15,    16,    17,    18,    19,     0,     0,    20,
    21,    22,    23,    24,    25,    26,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    27,    28,
     0,     0,     0,     0,     0,    29,     0,    30,     0,    31,
     0,     0,     0,     0,    32,     0,     0,     0,     0,     0,
    33,    34,     0,     0,    10,    35,    36,    13,    14,    15,
    16,    17,     0,     0,     0,     0,    20,    21,    22,    23,
    24,    25,    26,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    27,    28,     0,     0,     0,
     0,     0,    29,    84,     0,     0,    31,     0,     0,    85,
     0,    32,     0,     0,     0,     0,     0,    33,    34,     0,
     0,    10,    35,    36,    13,    14,    15,    16,    17,     0,
     0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    27,    28,     0,     0,     0,     0,     0,    29,
     0,     0,     0,    31,   140,     0,    85,     0,    32,     0,
     0,     0,     0,     0,    33,    34,     0,     0,    10,    35,
    36,    13,    14,    15,    16,    17,     0,     0,     0,     0,
    20,    21,    22,    23,    24,    25,    26,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
    28,     0,     0,     0,     0,     0,    29,   206,     0,     0,
    31,     0,     0,    85,     0,    32,     0,     0,     0,     0,
     0,    33,    34,     0,     0,    10,    35,    36,    13,    14,
    15,    16,    17,     0,     0,     0,     0,    20,    21,    22,
    23,    24,    25,    26,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    27,    28,     0,     0,
     0,     0,     0,    29,     0,    72,     0,    31,     0,     0,
     0,     0,    32,     0,     0,     0,     0,     0,    33,    34,
     0,     0,    10,    35,    36,    13,    14,    15,    16,    17,
     0,     0,     0,     0,    20,    21,    22,    23,    24,    25,
    26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    27,    28,     0,     0,     0,     0,     0,
    29,     0,    30,     0,    31,     0,     0,     0,     0,    32,
     0,     0,     0,     0,     0,    33,    34,     0,     0,    10,
    35,    36,    13,    14,    15,    16,    17,     0,     0,     0,
     0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    27,    28,     0,     0,     0,     0,     0,    29,     0,     0,
     0,    31,   183,     0,     0,     0,    32,     0,     0,     0,
     0,     0,    33,    34,     0,     0,    10,    35,    36,    13,
    14,    15,    16,    17,     0,     0,     0,     0,    20,    21,
    22,    23,    24,    25,    26,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    27,    28,     0,
     0,     0,     0,     0,    29,     0,   191,     0,    31,     0,
     0,     0,     0,    32,     0,     0,     0,     0,     0,    33,
    34,     0,     0,    10,    35,    36,    13,    14,    15,    16,
    17,     0,     0,     0,     0,    20,    21,    22,    23,    24,
    25,    26,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    27,    28,     0,     0,     0,     0,
     0,    29,     0,     0,     0,    31,   216,     0,     0,     0,
    32,     0,     0,     0,     0,     0,    33,    34,     0,     0,
    10,    35,    36,    13,    14,    15,    16,    17,     0,     0,
     0,     0,    20,    21,    22,    23,    24,    25,    26,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    27,    28,     0,     0,     0,     0,     0,    29,     0,
     0,     0,    31,     0,     0,    85,     0,    32,     0,     0,
     0,     0,     0,    33,    34,     0,     0,    10,    35,    36,
    13,    14,    15,    16,    17,     0,     0,     0,     0,    20,
    21,    22,    23,    24,    25,    26,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    27,    28,
     0,     0,     0,     0,     0,    29,     0,     0,     0,    31,
   229,     0,     0,     0,    32,     0,     0,     0,     0,     0,
    33,    34,     0,     0,    10,    35,    36,    13,    14,    15,
    16,    17,     0,     0,     0,     0,    20,    21,    22,    23,
    24,    25,    26,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    27,    28,     0,     0,     0,
     0,     0,    29,     0,     0,     0,    31,     0,     0,     0,
     0,    32,     0,     0,     0,     0,     0,    33,    34,     0,
     0,     0,    35,    36
};

static const short yycheck[] = {    12,
    80,    37,     0,     8,   149,    27,    28,    28,    55,     0,
    28,    59,    18,    59,    26,    27,    45,    46,    31,    24,
    25,   100,   101,    29,    59,    59,    32,    58,    76,    76,
    76,    58,    49,    50,    40,    57,    54,     6,    59,    37,
    56,    76,    76,    55,    13,    28,    37,    51,    52,    54,
    67,    68,    65,    66,    69,    70,   136,   202,    71,    26,
    27,    58,    68,    60,    61,    58,    63,     7,    81,    67,
    76,    77,   102,   103,   104,   105,    67,    58,    60,    61,
    78,    63,    71,    72,    73,    56,    57,    78,   110,   111,
   112,    56,   106,   107,    58,    58,    58,   108,   109,    58,
    56,     6,    34,    64,    56,    65,    54,   143,    66,   189,
   190,    31,   125,    57,   127,    62,   196,    59,   198,   132,
   126,    59,   128,   114,   115,   116,   117,   118,   119,   120,
   121,   122,   123,   124,    59,    59,   216,   150,    57,    62,
   153,    59,    58,   149,    56,   143,    54,    57,     9,    56,
    59,   231,   143,   233,    13,   235,    59,    59,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    60,    62,
     0,     0,    78,   253,   231,   239,   256,    67,   258,    96,
    57,    58,   195,    60,    61,   192,    63,   200,   194,   212,
    77,    95,   236,   199,   192,    -1,   202,    97,   211,   212,
    98,   192,    99,   199,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    16,    -1,   226,    -1,    -1,    21,    22,    23,    -1,
    -1,   234,    -1,    28,    29,    30,    31,    32,    33,    34,
   236,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   248,    -1,    -1,    -1,   259,    -1,     3,     4,
     5,    -1,    -1,     8,   260,    10,    11,    12,    63,    14,
    15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
    25,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
    55,    56,    -1,    58,    -1,    -1,    -1,    -1,    63,    -1,
    -1,    -1,    -1,    -1,    69,    70,     3,     4,     5,    74,
    75,     8,    -1,    10,    11,    12,    -1,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
    -1,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
    -1,    58,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,
    -1,    -1,    69,    70,     3,     4,     5,    74,    75,     8,
    -1,    10,    11,    12,    -1,    14,    15,    16,    17,    18,
    19,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
    -1,    -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    58,
    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,
    69,    70,    -1,    -1,    16,    74,    75,    19,    20,    21,
    22,    23,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
    -1,    -1,    54,    55,    -1,    -1,    58,    -1,    -1,    61,
    -1,    63,    -1,    -1,    -1,    -1,    -1,    69,    70,    -1,
    -1,    16,    74,    75,    19,    20,    21,    22,    23,    -1,
    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
    -1,    -1,    -1,    58,    59,    -1,    61,    -1,    63,    -1,
    -1,    -1,    -1,    -1,    69,    70,    -1,    -1,    16,    74,
    75,    19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,
    28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    -1,    -1,
    58,    -1,    -1,    61,    -1,    63,    -1,    -1,    -1,    -1,
    -1,    69,    70,    -1,    -1,    16,    74,    75,    19,    20,
    21,    22,    23,    -1,    -1,    -1,    -1,    28,    29,    30,
    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
    -1,    -1,    -1,    54,    -1,    56,    -1,    58,    -1,    -1,
    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    69,    70,
    -1,    -1,    16,    74,    75,    19,    20,    21,    22,    23,
    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
    54,    -1,    56,    -1,    58,    -1,    -1,    -1,    -1,    63,
    -1,    -1,    -1,    -1,    -1,    69,    70,    -1,    -1,    16,
    74,    75,    19,    20,    21,    22,    23,    -1,    -1,    -1,
    -1,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
    -1,    58,    59,    -1,    -1,    -1,    63,    -1,    -1,    -1,
    -1,    -1,    69,    70,    -1,    -1,    16,    74,    75,    19,
    20,    21,    22,    23,    -1,    -1,    -1,    -1,    28,    29,
    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,
    -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    58,    -1,
    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    69,
    70,    -1,    -1,    16,    74,    75,    19,    20,    21,    22,
    23,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
    -1,    54,    -1,    -1,    -1,    58,    59,    -1,    -1,    -1,
    63,    -1,    -1,    -1,    -1,    -1,    69,    70,    -1,    -1,
    16,    74,    75,    19,    20,    21,    22,    23,    -1,    -1,
    -1,    -1,    28,    29,    30,    31,    32,    33,    34,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    -1,
    -1,    -1,    58,    -1,    -1,    61,    -1,    63,    -1,    -1,
    -1,    -1,    -1,    69,    70,    -1,    -1,    16,    74,    75,
    19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,    28,
    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    58,
    59,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,
    69,    70,    -1,    -1,    16,    74,    75,    19,    20,    21,
    22,    23,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
    -1,    -1,    54,    -1,    -1,    -1,    58,    -1,    -1,    -1,
    -1,    63,    -1,    -1,    -1,    -1,    -1,    69,    70,    -1,
    -1,    -1,    74,    75
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         -2
#define YYEOF           0
#define YYACCEPT        return(0)
#define YYABORT         return(1)
#define YYERROR         goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL          goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do                                                              \
  if (yychar == YYEMPTY && yylen == 1)                          \
    { yychar = (token), yylval = (value);                       \
      yychar1 = YYTRANSLATE (yychar);                           \
      YYPOPSTACK;                                               \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    { yyerror ("syntax error: cannot back up"); YYERROR; }      \
while (0)

#define YYTERROR        1
#define YYERRCODE       256

#ifndef YYPURE
#define YYLEX           yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX           yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX           yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX           yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX           yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int     yychar;                 /*  the lookahead symbol                */
YYSTYPE yylval;                 /*  the semantic value of the           */
                                /*  lookahead symbol                    */

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;                 /*  location data for the lookahead     */
                                /*  symbol                              */
#endif

int yynerrs;                    /*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;                    /*  nonzero means print parse trace     */
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks       */

#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1                /* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)      __builtin_memcpy(TO,FROM,COUNT)
#else                           /* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;      /*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;              /*  lookahead token as an internal (translated) token number */

  short yyssa[YYINITDEPTH];     /*  the state stack                     */
  YYSTYPE yyvsa[YYINITDEPTH];   /*  the semantic value stack            */

  short *yyss = yyssa;          /*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;        /*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];   /*  the location stack                  */
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval = 0;                /*  the variable used to return         */
                                /*  semantic values from the action     */
                                /*  routines                            */

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;             /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = (short) yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = (int)(yyssp - yyss + 1); // _GD_ cast for 64bit build

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
         the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
         but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
                 &yyss1, size * sizeof (*yyssp),
                 &yyvs1, size * sizeof (*yyvsp),
                 &yyls1, size * sizeof (*yylsp),
                 &yystacksize);
#else
      yyoverflow("parser stack overflow",
                 &yyss1, size * sizeof (*yyssp),
                 &yyvs1, size * sizeof (*yyvsp),
                 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
        {
          yyerror("parser stack overflow");
          return 2;
        }
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
        yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
        fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
        YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
        fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)              /* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;           /* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
        fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
        {
          fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
          /* Give the individual parser a way to print the precise meaning
             of a token, for further debugging info.  */
#ifdef YYPRINT
          YYPRINT (stderr, yychar, yylval);
#endif
          fprintf (stderr, ")\n");
        }
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
               yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
        fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 129 "gmparser.y"
{
      g_codeTree = yyvsp[0];
    ;
    break;}
case 2:
#line 136 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 3:
#line 140 "gmparser.y"
{
      ATTACH(yyval, yyvsp[-1], yyvsp[0]);
    ;
    break;}
case 4:
#line 147 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 5:
#line 151 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 6:
#line 155 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 7:
#line 159 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 8:
#line 163 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 9:
#line 170 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_COMPOUND, gmlineno);
    ;
    break;}
case 10:
#line 174 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_COMPOUND, gmlineno);
      yyval->SetChild(0, yyvsp[-1]);
    ;
    break;}
case 11:
#line 182 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_DECLARATION, CTNDT_VARIABLE, gmlineno, (int)(gmptr) yyvsp[-2]);
      yyval->SetChild(0, yyvsp[-1]);
    ;
    break;}
case 12:
#line 187 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_DECLARATION, CTNDT_VARIABLE, gmlineno, (int)(gmptr) yyvsp[-4]);
      yyval->SetChild(0, yyvsp[-3]);
      ATTACH(yyval, yyval, CreateOperation(CTNOT_ASSIGN, yyvsp[-3], yyvsp[-1]));
    ;
    break;}
case 13:
#line 196 "gmparser.y"
{
      yyval = (YYSTYPE) CTVT_LOCAL;
    ;
    break;}
case 14:
#line 200 "gmparser.y"
{
      yyval = (YYSTYPE) CTVT_GLOBAL;
    ;
    break;}
case 15:
#line 204 "gmparser.y"
{
      yyval = (YYSTYPE) CTVT_MEMBER;
    ;
    break;}
case 16:
#line 210 "gmparser.y"
{
      yyval = NULL;
    ;
    break;}
case 17:
#line 214 "gmparser.y"
{
      yyval = yyvsp[-1];
    ;
    break;}
case 18:
#line 221 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_IF, (yyvsp[-2]) ? yyvsp[-2]->m_lineNumber : gmlineno);
      yyval->SetChild(0, yyvsp[-2]);
      yyval->SetChild(1, yyvsp[0]);
    ;
    break;}
case 19:
#line 227 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_IF, (yyvsp[-4]) ? yyvsp[-4]->m_lineNumber : gmlineno);
      yyval->SetChild(0, yyvsp[-4]);
      yyval->SetChild(1, yyvsp[-2]);
      yyval->SetChild(2, yyvsp[0]);
    ;
    break;}
case 20:
#line 234 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_IF, (yyvsp[-4]) ? yyvsp[-4]->m_lineNumber : gmlineno);
      yyval->SetChild(0, yyvsp[-4]);
      yyval->SetChild(1, yyvsp[-2]);
      yyval->SetChild(2, yyvsp[0]);
    ;
    break;}
case 21:
#line 241 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_FORK, (yyvsp[-1]) ? yyvsp[-1]->m_lineNumber : gmlineno );
      yyval->SetChild(0, yyvsp[0] );
      yyval->SetChild(1, yyvsp[-1] );
    ;
    break;}
case 22:
#line 247 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_FORK, (yyvsp[0]) ? yyvsp[0]->m_lineNumber : gmlineno );
      yyval->SetChild(0, yyvsp[0] );
    ;
    break;}
case 23:
#line 252 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_SWITCH, (yyvsp[-4]) ? yyvsp[-4]->m_lineNumber : gmlineno);
      yyval->SetChild(0, yyvsp[-4]);
      yyval->SetChild(1, yyvsp[-1]);
    ;
    break;}
case 24:
#line 262 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_CASE, (yyvsp[-1]) ? yyvsp[-1]->m_lineNumber : gmlineno);
      yyval->SetChild(0, yyvsp[-1]);
    ;
    break;}
case 25:
#line 268 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_CASE, (yyvsp[-2]) ? yyvsp[-2]->m_lineNumber : gmlineno);
      yyval->SetChild(0, yyvsp[-2]);
      yyval->SetChild(1, yyvsp[0]);
    ;
    break;}
case 26:
#line 274 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_DEFAULT, (yyvsp[0]) ? yyvsp[0]->m_lineNumber : gmlineno);
      yyval->SetChild(0, yyvsp[0]);
    ;
    break;}
case 27:
#line 282 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 28:
#line 286 "gmparser.y"
{
      ATTACH(yyval, yyvsp[-1], yyvsp[0]);
    ;
    break;}
case 29:
#line 293 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 30:
#line 297 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_ARRAY_INDEX, yyvsp[-3], yyvsp[-1]);
    ;
    break;}
case 31:
#line 301 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_DOT, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 32:
#line 308 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 33:
#line 312 "gmparser.y"
{
      yyval = yyvsp[0];
      yyval->m_flags |= gmCodeTreeNode::CTN_MEMBER;
    ;
    break;}
case 34:
#line 317 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_THIS, gmlineno);
    ;
    break;}
case 35:
#line 321 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 36:
#line 330 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_WHILE, (yyvsp[-2]) ? yyvsp[-2]->m_lineNumber : gmlineno);
      yyval->SetChild(0, yyvsp[-2]);
      yyval->SetChild(1, yyvsp[0]);
    ;
    break;}
case 37:
#line 336 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_DOWHILE, (yyvsp[-2]) ? yyvsp[-2]->m_lineNumber : gmlineno);
      yyval->SetChild(0, yyvsp[-2]);
      yyval->SetChild(1, yyvsp[0]);
    ;
    break;}
case 38:
#line 342 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_FOR, (yyvsp[-3]) ? yyvsp[-3]->m_lineNumber : gmlineno);
      yyval->SetChild(0, yyvsp[-3]);
      yyval->SetChild(1, yyvsp[-2]);
      yyval->SetChild(3, yyvsp[0]);
    ;
    break;}
case 39:
#line 349 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_FOR, (yyvsp[-4]) ? yyvsp[-4]->m_lineNumber : gmlineno);
      yyval->SetChild(0, yyvsp[-4]);
      yyval->SetChild(1, yyvsp[-3]);
      yyval->SetChild(2, yyvsp[-2]);
      yyval->SetChild(3, yyvsp[0]);
    ;
    break;}
case 40:
#line 357 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_FOREACH, (yyvsp[-2]) ? yyvsp[-2]->m_lineNumber : gmlineno);
      yyval->SetChild(0, yyvsp[-2]);
      yyval->SetChild(1, yyvsp[-4]);
      yyval->SetChild(3, yyvsp[0]);
    ;
    break;}
case 41:
#line 364 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_FOREACH, (yyvsp[-2]) ? yyvsp[-2]->m_lineNumber : gmlineno);
      yyval->SetChild(0, yyvsp[-2]);
      yyval->SetChild(1, yyvsp[-4]);
      yyval->SetChild(2, yyvsp[-6]);
      yyval->SetChild(3, yyvsp[0]);
    ;
    break;}
case 42:
#line 375 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_CONTINUE, gmlineno);
    ;
    break;}
case 43:
#line 379 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_BREAK, gmlineno);
    ;
    break;}
case 44:
#line 383 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_RETURN, gmlineno);
    ;
    break;}
case 45:
#line 387 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_STATEMENT, CTNST_RETURN, gmlineno);
      yyval->SetChild(0, yyvsp[-1]);
    ;
    break;}
case 46:
#line 395 "gmparser.y"
{
      yyval = yyvsp[0];
      if(yyval)
      {
        yyval->m_flags |= gmCodeTreeNode::CTN_POP;
      }
    ;
    break;}
case 47:
#line 403 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_ASSIGN, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 48:
#line 407 "gmparser.y"
{
      yyval = CreateAsignExpression(CTNOT_SHIFT_RIGHT, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 49:
#line 411 "gmparser.y"
{
      yyval = CreateAsignExpression(CTNOT_SHIFT_LEFT, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 50:
#line 415 "gmparser.y"
{
      yyval = CreateAsignExpression(CTNOT_ADD, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 51:
#line 419 "gmparser.y"
{
      yyval = CreateAsignExpression(CTNOT_MINUS, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 52:
#line 423 "gmparser.y"
{
      yyval = CreateAsignExpression(CTNOT_TIMES, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 53:
#line 427 "gmparser.y"
{
      yyval = CreateAsignExpression(CTNOT_DIVIDE, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 54:
#line 431 "gmparser.y"
{
      yyval = CreateAsignExpression(CTNOT_REM, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 55:
#line 435 "gmparser.y"
{
      yyval = CreateAsignExpression(CTNOT_BIT_AND, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 56:
#line 439 "gmparser.y"
{
      yyval = CreateAsignExpression(CTNOT_BIT_OR, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 57:
#line 443 "gmparser.y"
{
      yyval = CreateAsignExpression(CTNOT_BIT_XOR, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 58:
#line 451 "gmparser.y"
{
      yyval = NULL;
    ;
    break;}
case 59:
#line 455 "gmparser.y"
{
      yyval = yyvsp[-1];
    ;
    break;}
case 60:
#line 462 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 61:
#line 469 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 62:
#line 473 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_OR, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 63:
#line 480 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 64:
#line 484 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_AND, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 65:
#line 491 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 66:
#line 495 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_BIT_OR, yyvsp[-2], yyvsp[0]);
      yyval->ConstantFold();
    ;
    break;}
case 67:
#line 503 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 68:
#line 507 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_BIT_XOR, yyvsp[-2], yyvsp[0]);
      yyval->ConstantFold();
    ;
    break;}
case 69:
#line 515 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 70:
#line 519 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_BIT_AND, yyvsp[-2], yyvsp[0]);
      yyval->ConstantFold();
    ;
    break;}
case 71:
#line 527 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 72:
#line 531 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_EQ, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 73:
#line 535 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_NEQ, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 74:
#line 542 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 75:
#line 546 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_LT, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 76:
#line 550 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_GT, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 77:
#line 554 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_LTE, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 78:
#line 558 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_GTE, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 79:
#line 565 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 80:
#line 569 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_SHIFT_LEFT, yyvsp[-2], yyvsp[0]);
      yyval->ConstantFold();
    ;
    break;}
case 81:
#line 574 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_SHIFT_RIGHT, yyvsp[-2], yyvsp[0]);
      yyval->ConstantFold();
    ;
    break;}
case 82:
#line 582 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 83:
#line 586 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_ADD, yyvsp[-2], yyvsp[0]);
      yyval->ConstantFold();
    ;
    break;}
case 84:
#line 591 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_MINUS, yyvsp[-2], yyvsp[0]);
      yyval->ConstantFold();
    ;
    break;}
case 85:
#line 599 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 86:
#line 603 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_TIMES, yyvsp[-2], yyvsp[0]);
      yyval->ConstantFold();
    ;
    break;}
case 87:
#line 608 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_DIVIDE, yyvsp[-2], yyvsp[0]);
      yyval->ConstantFold();
    ;
    break;}
case 88:
#line 613 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_REM, yyvsp[-2], yyvsp[0]);
      yyval->ConstantFold();
    ;
    break;}
case 89:
#line 621 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 90:
#line 625 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_PRE_INC, yyvsp[0]);
    ;
    break;}
case 91:
#line 629 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_PRE_DEC, yyvsp[0]);
    ;
    break;}
case 92:
#line 633 "gmparser.y"
{
      yyval = yyvsp[-1];
      yyval->SetChild(0, yyvsp[0]);
      yyval->ConstantFold();
    ;
    break;}
case 93:
#line 642 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_UNARY_PLUS);
    ;
    break;}
case 94:
#line 646 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_UNARY_MINUS);
    ;
    break;}
case 95:
#line 650 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_UNARY_COMPLEMENT);
    ;
    break;}
case 96:
#line 654 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_UNARY_NOT);
    ;
    break;}
case 97:
#line 661 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 98:
#line 665 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_ARRAY_INDEX, yyvsp[-3], yyvsp[-1]);
    ;
    break;}
case 99:
#line 669 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CALL, gmlineno);
      yyval->SetChild(0, yyvsp[-2]);
    ;
    break;}
case 100:
#line 674 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CALL, gmlineno);
      yyval->SetChild(0, yyvsp[-3]);
      yyval->SetChild(1, yyvsp[-1]);
    ;
    break;}
case 101:
#line 680 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CALL, gmlineno);
      yyval->SetChild(0, yyvsp[-2]);
      yyval->SetChild(2, yyvsp[-4]);
    ;
    break;}
case 102:
#line 686 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CALL, gmlineno);
      yyval->SetChild(0, yyvsp[-3]);
      yyval->SetChild(1, yyvsp[-1]);
      yyval->SetChild(2, yyvsp[-5]);
    ;
    break;}
case 103:
#line 693 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_DOT, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 104:
#line 700 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 105:
#line 704 "gmparser.y"
{
      ATTACH(yyval, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 106:
#line 711 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_TABLE, gmlineno);
    ;
    break;}
case 107:
#line 715 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_TABLE, gmlineno);
      yyval->SetChild(0, yyvsp[-1]);
    ;
    break;}
case 108:
#line 720 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_TABLE, gmlineno);
    ;
    break;}
case 109:
#line 724 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_TABLE, gmlineno);
      yyval->SetChild(0, yyvsp[-1]);
    ;
    break;}
case 110:
#line 729 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_TABLE, gmlineno);
      yyval->SetChild(0, yyvsp[-2]);
    ;
    break;}
case 111:
#line 737 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_FUNCTION, gmlineno);
      yyval->SetChild(0, yyvsp[-2]);
      yyval->SetChild(1, yyvsp[0]);
    ;
    break;}
case 112:
#line 743 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_FUNCTION, gmlineno);
      yyval->SetChild(1, yyvsp[0]);
    ;
    break;}
case 113:
#line 751 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 114:
#line 755 "gmparser.y"
{
      ATTACH(yyval, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 115:
#line 762 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 116:
#line 766 "gmparser.y"
{
      yyval = CreateOperation(CTNOT_ASSIGN_FIELD, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 117:
#line 770 "gmparser.y"
{
	  yyval = CreateOperation(CTNOT_ASSIGN_INDEX, yyvsp[-3], yyvsp[0]);
	;
    break;}
case 118:
#line 778 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CONSTANT, gmlineno, CTNCT_INT);
      yyval->m_data.m_iValue = atoi(gmtext);
    ;
    break;}
case 119:
#line 786 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 120:
#line 790 "gmparser.y"
{
      ATTACH(yyval, yyvsp[-2], yyvsp[0]);
    ;
    break;}
case 121:
#line 797 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_DECLARATION, CTNDT_PARAMETER, gmlineno);
      yyval->SetChild(0, yyvsp[0]);
    ;
    break;}
case 122:
#line 802 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_DECLARATION, CTNDT_PARAMETER, gmlineno);
      yyval->SetChild(0, yyvsp[-2]);
      yyval->SetChild(1, yyvsp[0]);
    ;
    break;}
case 123:
#line 811 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 124:
#line 815 "gmparser.y"
{
      yyval = yyvsp[0];
      yyval->m_flags |= gmCodeTreeNode::CTN_MEMBER;
    ;
    break;}
case 125:
#line 820 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_THIS, gmlineno);
    ;
    break;}
case 126:
#line 824 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 127:
#line 828 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 128:
#line 832 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 129:
#line 836 "gmparser.y"
{
      yyval = yyvsp[-1];
    ;
    break;}
case 130:
#line 843 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_IDENTIFIER, gmlineno);
      yyval->m_data.m_string = (char *) gmCodeTree::Get().Alloc((int)strlen(gmtext) + 1);
      strcpy(yyval->m_data.m_string, gmtext);
    ;
    break;}
case 131:
#line 852 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CONSTANT, gmlineno, CTNCT_INT);
      yyval->m_data.m_iValue = strtoul(gmtext + 2, NULL, 16);
    ;
    break;}
case 132:
#line 857 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CONSTANT, gmlineno, CTNCT_INT);
      yyval->m_data.m_iValue = strtoul(gmtext + 2, NULL, 2);
    ;
    break;}
case 133:
#line 862 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CONSTANT, gmlineno, CTNCT_INT);
      yyval->m_data.m_iValue = atoi(gmtext);
    ;
    break;}
case 134:
#line 867 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CONSTANT, gmlineno, CTNCT_INT);
      yyval->m_data.m_iValue = 1;
    ;
    break;}
case 135:
#line 872 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CONSTANT, gmlineno, CTNCT_INT);
      yyval->m_data.m_iValue = 0;
    ;
    break;}
case 136:
#line 877 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CONSTANT, gmlineno, CTNCT_INT);

      char * c = (char *) gmCodeTree::Get().Alloc((int)strlen(gmtext) + 1);
      strcpy(c, gmtext);
      int result = 0;
      int shr = 0;

      while(*c)
      {
        if(c[0] == '\'')
        {
          ++c;
          continue;
        }
        else if(c[0] == '\\')
        {
          if(shr) result <<= 8;
          switch(c[1])
          {
            case 'a' : result |= (unsigned char) '\a'; break;
            case 'b' : result |= (unsigned char) '\b'; break;
            case 'f' : result |= (unsigned char) '\f'; break;
            case 'n' : result |= (unsigned char) '\n'; break;
            case 'r' : result |= (unsigned char) '\r'; break;
            case 't' : result |= (unsigned char) '\t'; break;
            case 'v' : result |= (unsigned char) '\v'; break;
            case '\'' : result |= (unsigned char) '\''; break;
            case '\"' : result |= (unsigned char) '\"'; break;
            case '\\' : result |= (unsigned char) '\\'; break;
            default: result |= (unsigned char) c[1];
          }
          ++shr;
          c += 2;
          continue;
        }
        if(shr) result <<= 8;
        result |= (unsigned char) *(c++);
        ++shr;
      }

      if(shr > 4 && gmCodeTree::Get().GetLog()) gmCodeTree::Get().GetLog()->LogEntry("truncated char, line %d", gmlineno);

      yyval->m_data.m_iValue = result;
    ;
    break;}
case 137:
#line 923 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CONSTANT, gmlineno, CTNCT_FLOAT);
      yyval->m_data.m_fValue = (float) atof(gmtext);
    ;
    break;}
case 138:
#line 928 "gmparser.y"
{
      yyval = yyvsp[0];
    ;
    break;}
case 139:
#line 932 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CONSTANT, gmlineno, CTNCT_NULL);
      yyval->m_data.m_iValue = 0;
    ;
    break;}
case 140:
#line 940 "gmparser.y"
{
      yyval = gmCodeTreeNode::Create(CTNT_EXPRESSION, CTNET_CONSTANT, gmlineno, CTNCT_STRING);
      yyval->m_data.m_string = (char *) gmCodeTree::Get().Alloc((int)strlen(gmtext) + 1);
      strcpy(yyval->m_data.m_string, gmtext);
      if(gmtext[0] == '"')
      {
        gmProcessDoubleQuoteString(yyval->m_data.m_string);
      }
      else if(gmtext[0] == '`')
      {
        gmProcessSingleQuoteString(yyval->m_data.m_string);
      }
    ;
    break;}
case 141:
#line 954 "gmparser.y"
{
      yyval = yyvsp[-1];
      int alen = (int)strlen(yyval->m_data.m_string);
      int blen = (int)strlen(gmtext);
      char * str = (char *) gmCodeTree::Get().Alloc(alen + blen + 1);
      if(str)
      {
        memcpy(str, yyvsp[-1]->m_data.m_string, alen);
        memcpy(str + alen, gmtext, blen);
        str[alen + blen] = '\0';
        if(str[alen] == '"')
        {
          gmProcessDoubleQuoteString(str + alen);
        }
        else if(str[alen] == '`')
        {
          gmProcessSingleQuoteString(str + alen);
        }
        yyval->m_data.m_string = str;
      }
    ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
        fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
        {
          int size = 0;
          char *msg;
          int x, count;

          count = 0;
          /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
          for (x = (yyn < 0 ? -yyn : 0);
               x < (int)(sizeof(yytname) / sizeof(char *)); x++) //_GD_
            if (yycheck[x + yyn] == x)
              size += (int)strlen(yytname[x]) + 15, count++; // _GD_ add cast for 64bit build
          //_GD_ msg = (char *) malloc(size + 15);
          msg = GM_NEW( char [size + 15] );
          if (msg != 0)
            {
              strcpy(msg, "parse error");

              if (count < 5)
                {
                  count = 0;
                  for (x = (yyn < 0 ? -yyn : 0);
                       x < (int)(sizeof(yytname) / sizeof(char *)); x++)
                    if (yycheck[x + yyn] == x)
                      {
                        strcat(msg, count == 0 ? ", expecting `" : " or `");
                        strcat(msg, yytname[x]);
                        strcat(msg, "'");
                        count++;
                      }
                }
              yyerror(msg);
              //_GD_ free(msg);
              delete [] msg;
            }
          else
            yyerror ("parse error; also virtual memory exceeded");
        }
      else
#endif /* YYERROR_VERBOSE */
        yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
        YYABORT;

#if YYDEBUG != 0
      if (yydebug)
        fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;              /* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
        fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
        goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 977 "gmparser.y"


#include <stdio.h>











