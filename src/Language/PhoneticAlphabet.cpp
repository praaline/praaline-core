#include <QString>
#include "PraalineCore/Language/PhoneticAlphabet.h"

PRAALINE_CORE_BEGIN_NAMESPACE

PhoneticAlphabet::PhoneticAlphabet()
{

}

QString PhoneticAlphabet::convertSAMPAtoIPAUnicode(const QString &sampa)
{
    QString ipa(sampa);
    // Vowels
    ipa.replace("A", "\u0251");    //    A 	65  script a        0251 	593 	open back unrounded, Cardinal 5, Eng. start
    ipa.replace("{", "\u00E6");    //    { 	123 ae ligature 	00E6 	230 	near-open front unrounded, Eng. trap
    ipa.replace("6", "\u0250");    //    6 	54 	turned a        0250 	592 	open schwa, Ger. besser
    ipa.replace("Q", "\u0252");    //    Q 	81 	turned script a 0252 	594 	open back rounded, Eng. lot
    ipa.replace("E", "\u025B");    //    E 	69 	epsilon         025B 	603 	open-mid front unrounded, C3, Fr. même
    ipa.replace("@", "\u0259");    //    @ 	64 	turned e        0259 	601 	schwa, Eng. banana
    ipa.replace("3", "\u025C");    //    3 	51 	rev. epsilon 	025C 	604 	long mid central, Eng. nurse
    ipa.replace("I", "\u026A");    //    I 	73 	small cap I 	026A 	618 	lax close front unrounded, Eng. kit
    ipa.replace("O", "\u0254");    //    O 	79 	turned c        0254 	596 	open-mid back rounded, Eng. thought
    ipa.replace("2", "\u00F8");    //    2 	50 	o-slash         00F8 	248 	close-mid front rounded, Fr. deux
    ipa.replace("9", "\u0153");    //    9 	57 	oe ligature 	0153 	339 	open-mid front rounded, Fr. neuf
    ipa.replace("&", "\u0276");    //    & 	38 	s.c. OE lig. 	0276 	630 	open front rounded
    ipa.replace("U", "\u028A");    //    U 	85 	upsilon         028A	650 	lax close back rounded, Eng. foot
    ipa.replace("}", "\u0289");    //    } 	125 barred u        0289 	649 	close central rounded, Swedish sju
    ipa.replace("V", "\u028C");    //    V 	86 	turned v        028C 	652 	open-mid back unrounded, Eng. strut
    ipa.replace("Y", "\u028F");    //    Y 	89 	small cap Y 	028F 	655 	lax [y], Ger. hübsch
    // Consonants
    ipa.replace("B", "\u03B2");    //    B 	66 	beta            03B2 	946 	voiced bilabial fricative, Sp. cabo
    ipa.replace("C", "\u00E7");    //    C 	67 	c-cedilla       00E7 	231 	voiceless palatal fricative, Ger. ich
    ipa.replace("D", "\u00F0");    //    D 	68 	eth             00F0 	240 	voiced dental fricative, Eng. then
    ipa.replace("G", "\u0263");    //    G 	71 	gamma           0263 	611 	voiced velar fricative, Sp. fuego
    ipa.replace("L", "\u028E");    //    L 	76 	turned y        028E 	654 	palatal lateral, It. famiglia
    ipa.replace("J", "\u0272");    //    J 	74 	left-tail n 	0272 	626 	palatal nasal, Sp. año
    ipa.replace("N", "\u014B");    //    N 	78 	eng             014B 	331 	velar nasal, Eng. thing
    ipa.replace("R", "\u0281");    //    R 	82 	inv. s.c. R 	0281 	641 	vd. uvular fric. or trill, Fr. roi
    ipa.replace("S", "\u0283");    //    S 	83 	esh             0283 	643 	voiceless palatoalveolar fricative, Eng. ship
    ipa.replace("T", "\u03B8");    //    T 	84 	theta           03B8 	952 	voiceless dental fricative, Eng. thin
    ipa.replace("H", "\u0265");    //    H 	72 	turned h        0265 	613 	labial-palatal semivowel, Fr. huit
    ipa.replace("Z", "\u0292");    //    Z 	90 	ezh (yogh)      0292 	658 	vd. palatoalveolar fric., Eng. measure
    ipa.replace("?", "\u0294");    //    ? 	63 	dotless ?       0294 	660 	glottal stop, Ger. Verein, also Danish stød
    // Length, stress and tone marks
    ipa.replace(":", "\u02D0");    //    : 	58 	length mark 	02D0 	720 	length mark
    ipa.replace("\"", "\u02C8");   //    " 	34 	vertical stroke 02C8 	712 	primary stress *
    ipa.replace("%", "\u02CC");    //    % 	37	low vert. str. 	02CC 	716 	secondary stress
    // Diacritics
    ipa.replace("~", "\u0303");    //    O~ 126 sup. tilde      0303 	771 	nasalization, Fr. bon
    return ipa;
}

PRAALINE_CORE_END_NAMESPACE
