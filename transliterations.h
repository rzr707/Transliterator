/**
    Буквари для разных стандартов, а также алфавиты украинского и русского языков
*/

#ifndef TRANSLITERATIONS_H
#define TRANSLITERATIONS_H

#include <QString>

// Русский язык
static QString strEngTranslate[33]                    // ALA-LC
=  {
	 "a",  "b",  "v",    "g", "d", "e",
     "ё",  "zh", "z",    "i", "ĭ", "k",
     "l",  "m",  "n",    "o", "p", "r",
	 "s",  "t",  "u",    "f", "kh","ts",
	 "ch", "sh", "shch", "\"", "y",
	 "'",  "ė",  "iu",   "ia"
   };

static QString strEngTranslateGost779[33]             // ГОСТ 7.79-2000А
=  {
	 "a", "b", "v", "g", "d", "e",
     "ё", "ž", "z", "i", "j", "k",
     "l", "m", "n", "o", "p", "r",
	 "s", "t", "u", "f", "h", "с",
	 "č", "š", "ŝ", "\"","y", "'",
	 "è", "û", "â"
   };

static QString strEngTranslateGost16878[33]            // ГОСТ 16876-71-2
=  { 
	 "a",  "b",  "v",   "g",  "d",  "e",
     "jo", "zh", "z",   "i",  "jj", "k",
     "l",  "m",  "n",   "o",  "p",  "r",
	 "s",  "t",  "u",   "f",  "kh", "с",
	 "ch", "sh", "shh", "\"", "y",  "'",
	 "eh", "ju", "ja"
   };

static QString strRusTranslate = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
static QString strUkrTranslate = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя'";


// Украинский язык
static QString strUkrEngTranslate[34] =                 // паспортная транслитерация КМУ 2010
{
    "a", "b", "v", "gh", "g", "d", "e", "ye", "zh", "z",
    "y", "i", "yi", "y", "k", "l", "m", "n", "o", "p",
    "r", "s", "t", "u", "f", "kh", "ts", "ch", "sh", "shch",
    "'", "yu", "ya", "\""
};

static QString strUkrEngBgnPcgn[34] =                   // американская (BGN/PCGN 1965)
{
    "a", "b", "v", "h", "g", "d", "e", "ye", "zh", "z",
    "y", "i", "yi", "y", "k", "l", "m", "n", "o", "p",
    "r", "s", "t", "u", "f", "kh", "ts", "ch", "sh", "shch",
    "´", "yu", "ya", "\""
};

static QString strUkrEngGeographical[34] =              // Географическая УКППТ 1996
{
    "a", "b", "v", "h", "g", "d", "e", "ye", "zh", "z",  //ye zh
    "y", "i", "yi", "y", "k", "l", "m", "n", "o", "p",   //yi
    "r", "s", "t", "u", "f", "kh", "ts", "ch", "sh", "shch",
    "´", "yu", "ya", "'"
};

#endif // TRANSLITERATIONS_H

