/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_SQL_USERS_NIKKI_DEVELOPMENT_DREAM_HOTEL_VENDOR_MONETDB_BUILD_SQL_SERVER_SQL_PARSER_TAB_H_INCLUDED
# define YY_SQL_USERS_NIKKI_DEVELOPMENT_DREAM_HOTEL_VENDOR_MONETDB_BUILD_SQL_SERVER_SQL_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int sqldebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    STRING = 258,                  /* STRING  */
    USTRING = 259,                 /* USTRING  */
    XSTRING = 260,                 /* XSTRING  */
    IDENT = 261,                   /* IDENT  */
    UIDENT = 262,                  /* UIDENT  */
    aTYPE = 263,                   /* aTYPE  */
    ALIAS = 264,                   /* ALIAS  */
    RANK = 265,                    /* RANK  */
    sqlINT = 266,                  /* sqlINT  */
    OIDNUM = 267,                  /* OIDNUM  */
    HEXADECIMAL = 268,             /* HEXADECIMAL  */
    INTNUM = 269,                  /* INTNUM  */
    APPROXNUM = 270,               /* APPROXNUM  */
    USING = 271,                   /* USING  */
    GLOBAL = 272,                  /* GLOBAL  */
    CAST = 273,                    /* CAST  */
    CONVERT = 274,                 /* CONVERT  */
    CHARACTER = 275,               /* CHARACTER  */
    VARYING = 276,                 /* VARYING  */
    LARGE = 277,                   /* LARGE  */
    OBJECT = 278,                  /* OBJECT  */
    VARCHAR = 279,                 /* VARCHAR  */
    CLOB = 280,                    /* CLOB  */
    sqlTEXT = 281,                 /* sqlTEXT  */
    BINARY = 282,                  /* BINARY  */
    sqlBLOB = 283,                 /* sqlBLOB  */
    sqlDECIMAL = 284,              /* sqlDECIMAL  */
    sqlFLOAT = 285,                /* sqlFLOAT  */
    TINYINT = 286,                 /* TINYINT  */
    SMALLINT = 287,                /* SMALLINT  */
    BIGINT = 288,                  /* BIGINT  */
    HUGEINT = 289,                 /* HUGEINT  */
    sqlINTEGER = 290,              /* sqlINTEGER  */
    sqlDOUBLE = 291,               /* sqlDOUBLE  */
    sqlREAL = 292,                 /* sqlREAL  */
    PRECISION = 293,               /* PRECISION  */
    PARTIAL = 294,                 /* PARTIAL  */
    SIMPLE = 295,                  /* SIMPLE  */
    ACTION = 296,                  /* ACTION  */
    CASCADE = 297,                 /* CASCADE  */
    RESTRICT = 298,                /* RESTRICT  */
    BOOL_FALSE = 299,              /* BOOL_FALSE  */
    BOOL_TRUE = 300,               /* BOOL_TRUE  */
    CURRENT_DATE = 301,            /* CURRENT_DATE  */
    CURRENT_TIMESTAMP = 302,       /* CURRENT_TIMESTAMP  */
    CURRENT_TIME = 303,            /* CURRENT_TIME  */
    LOCALTIMESTAMP = 304,          /* LOCALTIMESTAMP  */
    LOCALTIME = 305,               /* LOCALTIME  */
    BIG = 306,                     /* BIG  */
    LITTLE = 307,                  /* LITTLE  */
    NATIVE = 308,                  /* NATIVE  */
    ENDIAN = 309,                  /* ENDIAN  */
    LEX_ERROR = 310,               /* LEX_ERROR  */
    GEOMETRY = 311,                /* GEOMETRY  */
    GEOMETRYSUBTYPE = 312,         /* GEOMETRYSUBTYPE  */
    GEOMETRYA = 313,               /* GEOMETRYA  */
    USER = 314,                    /* USER  */
    CURRENT_USER = 315,            /* CURRENT_USER  */
    SESSION_USER = 316,            /* SESSION_USER  */
    LOCAL = 317,                   /* LOCAL  */
    BEST = 318,                    /* BEST  */
    EFFORT = 319,                  /* EFFORT  */
    CURRENT_ROLE = 320,            /* CURRENT_ROLE  */
    sqlSESSION = 321,              /* sqlSESSION  */
    CURRENT_SCHEMA = 322,          /* CURRENT_SCHEMA  */
    CURRENT_TIMEZONE = 323,        /* CURRENT_TIMEZONE  */
    sqlDELETE = 324,               /* sqlDELETE  */
    UPDATE = 325,                  /* UPDATE  */
    SELECT = 326,                  /* SELECT  */
    INSERT = 327,                  /* INSERT  */
    MATCHED = 328,                 /* MATCHED  */
    LATERAL = 329,                 /* LATERAL  */
    LEFT = 330,                    /* LEFT  */
    RIGHT = 331,                   /* RIGHT  */
    FULL = 332,                    /* FULL  */
    OUTER = 333,                   /* OUTER  */
    NATURAL = 334,                 /* NATURAL  */
    CROSS = 335,                   /* CROSS  */
    JOIN = 336,                    /* JOIN  */
    INNER = 337,                   /* INNER  */
    COMMIT = 338,                  /* COMMIT  */
    ROLLBACK = 339,                /* ROLLBACK  */
    SAVEPOINT = 340,               /* SAVEPOINT  */
    RELEASE = 341,                 /* RELEASE  */
    WORK = 342,                    /* WORK  */
    CHAIN = 343,                   /* CHAIN  */
    NO = 344,                      /* NO  */
    PRESERVE = 345,                /* PRESERVE  */
    ROWS = 346,                    /* ROWS  */
    START = 347,                   /* START  */
    TRANSACTION = 348,             /* TRANSACTION  */
    READ = 349,                    /* READ  */
    WRITE = 350,                   /* WRITE  */
    ONLY = 351,                    /* ONLY  */
    ISOLATION = 352,               /* ISOLATION  */
    LEVEL = 353,                   /* LEVEL  */
    UNCOMMITTED = 354,             /* UNCOMMITTED  */
    COMMITTED = 355,               /* COMMITTED  */
    sqlREPEATABLE = 356,           /* sqlREPEATABLE  */
    SERIALIZABLE = 357,            /* SERIALIZABLE  */
    DIAGNOSTICS = 358,             /* DIAGNOSTICS  */
    sqlSIZE = 359,                 /* sqlSIZE  */
    STORAGE = 360,                 /* STORAGE  */
    SNAPSHOT = 361,                /* SNAPSHOT  */
    ASYMMETRIC = 362,              /* ASYMMETRIC  */
    SYMMETRIC = 363,               /* SYMMETRIC  */
    ORDER = 364,                   /* ORDER  */
    ORDERED = 365,                 /* ORDERED  */
    BY = 366,                      /* BY  */
    IMPRINTS = 367,                /* IMPRINTS  */
    ESCAPE = 368,                  /* ESCAPE  */
    UESCAPE = 369,                 /* UESCAPE  */
    HAVING = 370,                  /* HAVING  */
    sqlGROUP = 371,                /* sqlGROUP  */
    ROLLUP = 372,                  /* ROLLUP  */
    CUBE = 373,                    /* CUBE  */
    sqlNULL = 374,                 /* sqlNULL  */
    GROUPING = 375,                /* GROUPING  */
    SETS = 376,                    /* SETS  */
    FROM = 377,                    /* FROM  */
    FOR = 378,                     /* FOR  */
    MATCH = 379,                   /* MATCH  */
    EXTRACT = 380,                 /* EXTRACT  */
    SEQUENCE = 381,                /* SEQUENCE  */
    INCREMENT = 382,               /* INCREMENT  */
    RESTART = 383,                 /* RESTART  */
    CONTINUE = 384,                /* CONTINUE  */
    MAXVALUE = 385,                /* MAXVALUE  */
    MINVALUE = 386,                /* MINVALUE  */
    CYCLE = 387,                   /* CYCLE  */
    NEXT = 388,                    /* NEXT  */
    VALUE = 389,                   /* VALUE  */
    CACHE = 390,                   /* CACHE  */
    GENERATED = 391,               /* GENERATED  */
    ALWAYS = 392,                  /* ALWAYS  */
    IDENTITY = 393,                /* IDENTITY  */
    SERIAL = 394,                  /* SERIAL  */
    BIGSERIAL = 395,               /* BIGSERIAL  */
    AUTO_INCREMENT = 396,          /* AUTO_INCREMENT  */
    SCOLON = 397,                  /* SCOLON  */
    AT = 398,                      /* AT  */
    XMLCOMMENT = 399,              /* XMLCOMMENT  */
    XMLCONCAT = 400,               /* XMLCONCAT  */
    XMLDOCUMENT = 401,             /* XMLDOCUMENT  */
    XMLELEMENT = 402,              /* XMLELEMENT  */
    XMLATTRIBUTES = 403,           /* XMLATTRIBUTES  */
    XMLFOREST = 404,               /* XMLFOREST  */
    XMLPARSE = 405,                /* XMLPARSE  */
    STRIP = 406,                   /* STRIP  */
    WHITESPACE = 407,              /* WHITESPACE  */
    XMLPI = 408,                   /* XMLPI  */
    XMLQUERY = 409,                /* XMLQUERY  */
    PASSING = 410,                 /* PASSING  */
    XMLTEXT = 411,                 /* XMLTEXT  */
    NIL = 412,                     /* NIL  */
    REF = 413,                     /* REF  */
    ABSENT = 414,                  /* ABSENT  */
    EMPTY = 415,                   /* EMPTY  */
    DOCUMENT = 416,                /* DOCUMENT  */
    ELEMENT = 417,                 /* ELEMENT  */
    CONTENT = 418,                 /* CONTENT  */
    XMLNAMESPACES = 419,           /* XMLNAMESPACES  */
    NAMESPACE = 420,               /* NAMESPACE  */
    XMLVALIDATE = 421,             /* XMLVALIDATE  */
    RETURNING = 422,               /* RETURNING  */
    LOCATION = 423,                /* LOCATION  */
    ID = 424,                      /* ID  */
    ACCORDING = 425,               /* ACCORDING  */
    XMLSCHEMA = 426,               /* XMLSCHEMA  */
    URI = 427,                     /* URI  */
    XMLAGG = 428,                  /* XMLAGG  */
    FILTER = 429,                  /* FILTER  */
    UNION = 430,                   /* UNION  */
    EXCEPT = 431,                  /* EXCEPT  */
    INTERSECT = 432,               /* INTERSECT  */
    CORRESPONDING = 433,           /* CORRESPONDING  */
    DATA = 434,                    /* DATA  */
    NOT = 435,                     /* NOT  */
    ALL = 436,                     /* ALL  */
    ANY = 437,                     /* ANY  */
    NOT_BETWEEN = 438,             /* NOT_BETWEEN  */
    BETWEEN = 439,                 /* BETWEEN  */
    NOT_IN = 440,                  /* NOT_IN  */
    sqlIN = 441,                   /* sqlIN  */
    NOT_EXISTS = 442,              /* NOT_EXISTS  */
    EXISTS = 443,                  /* EXISTS  */
    NOT_LIKE = 444,                /* NOT_LIKE  */
    LIKE = 445,                    /* LIKE  */
    NOT_ILIKE = 446,               /* NOT_ILIKE  */
    ILIKE = 447,                   /* ILIKE  */
    OR = 448,                      /* OR  */
    SOME = 449,                    /* SOME  */
    AND = 450,                     /* AND  */
    COMPARISON = 451,              /* COMPARISON  */
    LEFT_SHIFT = 452,              /* LEFT_SHIFT  */
    RIGHT_SHIFT = 453,             /* RIGHT_SHIFT  */
    LEFT_SHIFT_ASSIGN = 454,       /* LEFT_SHIFT_ASSIGN  */
    RIGHT_SHIFT_ASSIGN = 455,      /* RIGHT_SHIFT_ASSIGN  */
    CONCATSTRING = 456,            /* CONCATSTRING  */
    SUBSTRING = 457,               /* SUBSTRING  */
    POSITION = 458,                /* POSITION  */
    SPLIT_PART = 459,              /* SPLIT_PART  */
    UMINUS = 460,                  /* UMINUS  */
    GEOM_OVERLAP = 461,            /* GEOM_OVERLAP  */
    GEOM_OVERLAP_OR_ABOVE = 462,   /* GEOM_OVERLAP_OR_ABOVE  */
    GEOM_OVERLAP_OR_BELOW = 463,   /* GEOM_OVERLAP_OR_BELOW  */
    GEOM_OVERLAP_OR_LEFT = 464,    /* GEOM_OVERLAP_OR_LEFT  */
    GEOM_OVERLAP_OR_RIGHT = 465,   /* GEOM_OVERLAP_OR_RIGHT  */
    GEOM_BELOW = 466,              /* GEOM_BELOW  */
    GEOM_ABOVE = 467,              /* GEOM_ABOVE  */
    GEOM_DIST = 468,               /* GEOM_DIST  */
    GEOM_MBR_EQUAL = 469,          /* GEOM_MBR_EQUAL  */
    TEMP = 470,                    /* TEMP  */
    TEMPORARY = 471,               /* TEMPORARY  */
    MERGE = 472,                   /* MERGE  */
    REMOTE = 473,                  /* REMOTE  */
    REPLICA = 474,                 /* REPLICA  */
    UNLOGGED = 475,                /* UNLOGGED  */
    ASC = 476,                     /* ASC  */
    DESC = 477,                    /* DESC  */
    AUTHORIZATION = 478,           /* AUTHORIZATION  */
    CHECK = 479,                   /* CHECK  */
    CONSTRAINT = 480,              /* CONSTRAINT  */
    CREATE = 481,                  /* CREATE  */
    COMMENT = 482,                 /* COMMENT  */
    NULLS = 483,                   /* NULLS  */
    FIRST = 484,                   /* FIRST  */
    LAST = 485,                    /* LAST  */
    TYPE = 486,                    /* TYPE  */
    PROCEDURE = 487,               /* PROCEDURE  */
    FUNCTION = 488,                /* FUNCTION  */
    sqlLOADER = 489,               /* sqlLOADER  */
    AGGREGATE = 490,               /* AGGREGATE  */
    RETURNS = 491,                 /* RETURNS  */
    EXTERNAL = 492,                /* EXTERNAL  */
    sqlNAME = 493,                 /* sqlNAME  */
    DECLARE = 494,                 /* DECLARE  */
    CALL = 495,                    /* CALL  */
    LANGUAGE = 496,                /* LANGUAGE  */
    ANALYZE = 497,                 /* ANALYZE  */
    MINMAX = 498,                  /* MINMAX  */
    SQL_EXPLAIN = 499,             /* SQL_EXPLAIN  */
    SQL_PLAN = 500,                /* SQL_PLAN  */
    SQL_DEBUG = 501,               /* SQL_DEBUG  */
    SQL_TRACE = 502,               /* SQL_TRACE  */
    PREP = 503,                    /* PREP  */
    PREPARE = 504,                 /* PREPARE  */
    EXEC = 505,                    /* EXEC  */
    EXECUTE = 506,                 /* EXECUTE  */
    DEALLOCATE = 507,              /* DEALLOCATE  */
    DEFAULT = 508,                 /* DEFAULT  */
    DISTINCT = 509,                /* DISTINCT  */
    DROP = 510,                    /* DROP  */
    TRUNCATE = 511,                /* TRUNCATE  */
    FOREIGN = 512,                 /* FOREIGN  */
    RENAME = 513,                  /* RENAME  */
    ENCRYPTED = 514,               /* ENCRYPTED  */
    UNENCRYPTED = 515,             /* UNENCRYPTED  */
    PASSWORD = 516,                /* PASSWORD  */
    GRANT = 517,                   /* GRANT  */
    REVOKE = 518,                  /* REVOKE  */
    ROLE = 519,                    /* ROLE  */
    ADMIN = 520,                   /* ADMIN  */
    INTO = 521,                    /* INTO  */
    IS = 522,                      /* IS  */
    KEY = 523,                     /* KEY  */
    ON = 524,                      /* ON  */
    OPTION = 525,                  /* OPTION  */
    OPTIONS = 526,                 /* OPTIONS  */
    PATH = 527,                    /* PATH  */
    PRIMARY = 528,                 /* PRIMARY  */
    PRIVILEGES = 529,              /* PRIVILEGES  */
    PUBLIC = 530,                  /* PUBLIC  */
    REFERENCES = 531,              /* REFERENCES  */
    SCHEMA = 532,                  /* SCHEMA  */
    SET = 533,                     /* SET  */
    AUTO_COMMIT = 534,             /* AUTO_COMMIT  */
    RETURN = 535,                  /* RETURN  */
    ALTER = 536,                   /* ALTER  */
    ADD = 537,                     /* ADD  */
    TABLE = 538,                   /* TABLE  */
    COLUMN = 539,                  /* COLUMN  */
    TO = 540,                      /* TO  */
    UNIQUE = 541,                  /* UNIQUE  */
    VALUES = 542,                  /* VALUES  */
    VIEW = 543,                    /* VIEW  */
    WHERE = 544,                   /* WHERE  */
    WITH = 545,                    /* WITH  */
    sqlDATE = 546,                 /* sqlDATE  */
    TIME = 547,                    /* TIME  */
    TIMESTAMP = 548,               /* TIMESTAMP  */
    INTERVAL = 549,                /* INTERVAL  */
    CENTURY = 550,                 /* CENTURY  */
    DECADE = 551,                  /* DECADE  */
    YEAR = 552,                    /* YEAR  */
    QUARTER = 553,                 /* QUARTER  */
    DOW = 554,                     /* DOW  */
    DOY = 555,                     /* DOY  */
    MONTH = 556,                   /* MONTH  */
    WEEK = 557,                    /* WEEK  */
    DAY = 558,                     /* DAY  */
    HOUR = 559,                    /* HOUR  */
    MINUTE = 560,                  /* MINUTE  */
    SECOND = 561,                  /* SECOND  */
    EPOCH = 562,                   /* EPOCH  */
    ZONE = 563,                    /* ZONE  */
    LIMIT = 564,                   /* LIMIT  */
    OFFSET = 565,                  /* OFFSET  */
    SAMPLE = 566,                  /* SAMPLE  */
    SEED = 567,                    /* SEED  */
    CASE = 568,                    /* CASE  */
    WHEN = 569,                    /* WHEN  */
    THEN = 570,                    /* THEN  */
    ELSE = 571,                    /* ELSE  */
    NULLIF = 572,                  /* NULLIF  */
    COALESCE = 573,                /* COALESCE  */
    IF = 574,                      /* IF  */
    ELSEIF = 575,                  /* ELSEIF  */
    WHILE = 576,                   /* WHILE  */
    DO = 577,                      /* DO  */
    ATOMIC = 578,                  /* ATOMIC  */
    BEGIN = 579,                   /* BEGIN  */
    END = 580,                     /* END  */
    COPY = 581,                    /* COPY  */
    RECORDS = 582,                 /* RECORDS  */
    DELIMITERS = 583,              /* DELIMITERS  */
    STDIN = 584,                   /* STDIN  */
    STDOUT = 585,                  /* STDOUT  */
    FWF = 586,                     /* FWF  */
    CLIENT = 587,                  /* CLIENT  */
    SERVER = 588,                  /* SERVER  */
    INDEX = 589,                   /* INDEX  */
    REPLACE = 590,                 /* REPLACE  */
    AS = 591,                      /* AS  */
    TRIGGER = 592,                 /* TRIGGER  */
    OF = 593,                      /* OF  */
    BEFORE = 594,                  /* BEFORE  */
    AFTER = 595,                   /* AFTER  */
    ROW = 596,                     /* ROW  */
    STATEMENT = 597,               /* STATEMENT  */
    sqlNEW = 598,                  /* sqlNEW  */
    OLD = 599,                     /* OLD  */
    EACH = 600,                    /* EACH  */
    REFERENCING = 601,             /* REFERENCING  */
    OVER = 602,                    /* OVER  */
    PARTITION = 603,               /* PARTITION  */
    CURRENT = 604,                 /* CURRENT  */
    EXCLUDE = 605,                 /* EXCLUDE  */
    FOLLOWING = 606,               /* FOLLOWING  */
    PRECEDING = 607,               /* PRECEDING  */
    OTHERS = 608,                  /* OTHERS  */
    TIES = 609,                    /* TIES  */
    RANGE = 610,                   /* RANGE  */
    UNBOUNDED = 611,               /* UNBOUNDED  */
    GROUPS = 612,                  /* GROUPS  */
    WINDOW = 613,                  /* WINDOW  */
    X_BODY = 614,                  /* X_BODY  */
    MAX_MEMORY = 615,              /* MAX_MEMORY  */
    MAX_WORKERS = 616,             /* MAX_WORKERS  */
    OPTIMIZER = 617                /* OPTIMIZER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 175 "sql_parser.y"

	int		i_val,bval;
	lng		l_val,operation;
	double		fval;
	char *		sval;
	symbol*		sym;
	dlist*		l;
	sql_subtype	type;

#line 436 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int sqlparse (mvc *m);


#endif /* !YY_SQL_USERS_NIKKI_DEVELOPMENT_DREAM_HOTEL_VENDOR_MONETDB_BUILD_SQL_SERVER_SQL_PARSER_TAB_H_INCLUDED  */
