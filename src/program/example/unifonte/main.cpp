/*

  Glt OpenGL C++ Toolkit (Glt)
  Copyright (C) 2000-2001 Nigel Stewart
  Email: nigels@nigels.com   WWW: http://www.nigels.com/glt/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include <glutm/main.h>
#include <glutm/master.h>
#include <glutm/window.h>

#include <glt/fontunic.h>
#include <glt/color.h>
#include <glt/texture.h>

#include <node/text.h>
#include <node/tiled.h>

#include <unifont/unifont.h>

#include <misc/string.h>
#include <misc/hex.h>

#include "textures.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
using namespace std;

#ifdef GLT_UNICODE

class GlutWindowUnicodeFontDemo : public GlutWindow
{
public:
    GlutWindowUnicodeFontDemo
    (
        const std::string &title,
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault,
        unsigned int displayMode = displayModeDefault
    );

   ~GlutWindowUnicodeFontDemo();

   void OnOpen();
   void OnClose();
   void OnDisplay();
   void OnReshape(int w, int h);
   void OnKeyboard(unsigned char key, int x, int y);
   void OnSpecial(int key, int x, int y);
   void OnMenu(int value);

   bool loadUnicodeText(const std::string &filename);

protected:

    typedef enum
    {
        UFONT_SAMPLE_GERMAN,
        UFONT_SAMPLE_GREEK,
        UFONT_SAMPLE_CHINESE,
        UFONT_SAMPLE_JAPANESE,
        UFONT_SAMPLE_AUSTRALIAN,
        UFONT_SAMPLE_RUSSIAN,
        UFONT_SAMPLE_UNITEDKINGDOM,

        UFONT_SHOW_BASIC_LATIN,                     /* U+0000..U+007F */
        UFONT_SHOW_LATIN1_SUPPLEMENT,               /* U+0080..U+00FF */
        UFONT_SHOW_LATIN_EXTENDED_A,                /* U+0100..U+017F */
        UFONT_SHOW_LATIN_EXTENDED_B,                /* U+0180..U+024F */
        UFONT_SHOW_IPA_EXTENSIONS,                  /* U+0250..U+02AF */
        UFONT_SHOW_SPACING_MODIFIER_LETTERS,        /* U+02B0..U+02FF */
        UFONT_SHOW_COMBINING_DIACRITICAL_MARKS,     /* U+0300..U+036F */
        UFONT_SHOW_GREEK,                           /* U+0370..U+03FF */
        UFONT_SHOW_CYRILLIC,                        /* U+0400..U+04FF */
        UFONT_SHOW_ARMENIAN,                        /* U+0530..U+058F */
        UFONT_SHOW_HEBREW,                          /* U+0590..U+05FF */
        UFONT_SHOW_ARABIC,                          /* U+0600..U+06FF */
        UFONT_SHOW_THAI,                            /* U+0E00..U+0E7F */
        UFONT_SHOW_LAO,                             /* U+0E80..U+0EFF */
        UFONT_SHOW_GEORGIAN,                        /* U+10A0..U+10FF */
        UFONT_SHOW_ETHIOPIC,                        /* U+1200..U+137F */
        UFONT_SHOW_LATIN_EXTENDED_ADDITIONAL,       /* U+1E00..U+1EFF */
        UFONT_SHOW_GREEK_EXTENDED,                  /* U+1F00..U+1FFF */
        UFONT_SHOW_GENERAL_PUNCTUATION,             /* U+2000..U+206F */
        UFONT_SHOW_SUPERSCRIPTS_AND_SUBSCRIPTS,     /* U+2070..U+209F */
        UFONT_SHOW_CURRENCY_SYMBOLS,                /* U+20A0..U+20CF */
        UFONT_SHOW_COMBINING_MARKS_FOR_SYMBOLS,     /* U+20D0..U+20FF */
        UFONT_SHOW_LETTERLIKE_SYMBOLS,              /* U+2100..U+214F */
        UFONT_SHOW_NUMBER_FORMS,                    /* U+2150..U+218F */
        UFONT_SHOW_ARROWS,                          /* U+2190..U+21FF */
        UFONT_SHOW_MATHEMATICAL_OPERATORS,          /* U+2200..U+22FF */
        UFONT_SHOW_MISCELLANEOUS_TECHNICAL,         /* U+2300..U+23FF */
        UFONT_SHOW_CONTROL_PICTURES,                /* U+2400..U+243F */
        UFONT_SHOW_OPTICAL_CHARACTER_RECOGNITION,   /* U+2440..U+245F */
        UFONT_SHOW_ENCLOSED_ALPHANUMERICS,          /* U+2460..U+24FF */
        UFONT_SHOW_BOX_DRAWING,                     /* U+2500..U+257F */
        UFONT_SHOW_BLOCK_ELEMENTS,                  /* U+2580..U+259F */
        UFONT_SHOW_GEOMETRIC_SHAPES,                /* U+25A0..U+25FF */
        UFONT_SHOW_MISCELLANEOUS_SYMBOLS,           /* U+2600..U+26FF */
        UFONT_SHOW_DINGBATS,                        /* U+2700..U+27BF */
        UFONT_SHOW_BRAILLE_PATTERN_SYMBOLS,         /* U+2800..U+28FF */
        UFONT_SHOW_CJK_SYMBOLS_AND_PUNCTUATION,     /* U+3000..U+303F */
        UFONT_SHOW_HIRAGANA,                        /* U+3040..U+309F */
        UFONT_SHOW_KATAKANA,                        /* U+30A0..U+30FF */
        UFONT_SHOW_BOPOMOFO,                        /* U+3100..U+312F */
        UFONT_SHOW_HANGUL_COMPATIBILITY_JAMO,       /* U+3130..U+318F */
        UFONT_SHOW_ENCLOSED_CJK_LETTERS_AND_MONTHS, /* U+3200..U+32FF */
        UFONT_SHOW_CJK_COMPATIBILITY,               /* U+3300..U+33FF */
        UFONT_SHOW_CJK_UNIFIED_IDEOGRAPHS,          /* U+4E00..U+9FFF */
        UFONT_SHOW_HANGUL_SYLLABLES,                /* U+AC00..U+D7A3 */
        UFONT_SHOW_CJK_COMPATIBILITY_IDEOGRAPHS,    /* U+F900..U+FAFF */
        UFONT_SHOW_ALPHABETIC_PRESENTATION_FORMS,   /* U+FB00..U+FB4F */
        UFONT_SHOW_ARABIC_PRESENTATION_FORMS_A,     /* U+FB50..U+FDFF */
        UFONT_SHOW_COMBINING_HALF_MARKS,            /* U+FE20..U+FE2F */
        UFONT_SHOW_CJK_COMPATIBILITY_FORMS,         /* U+FE30..U+FE4F */
        UFONT_SHOW_SMALL_FORM_VARIANTS,             /* U+FE50..U+FE6F */
        UFONT_SHOW_ARABIC_PRESENTATION_FORMS_B,     /* U+FE70..U+FEFF */
        UFONT_SHOW_HALFWIDTH_AND_FULLWIDTH_FORMS,   /* U+FF00..U+FFEF */
        UFONT_SHOW_SPECIALS,                        /* U+FFF0..U+FFFF */

    } MenuCallbacks;

    GltFontUnicode      _font;
    GltTextOverlay      _info;

    GltTexture          _texture;
    GltTextureViewport  _background;

    bool                _browse;
    bool                _update;

    wchar_t        _offset;
    int            _rows;
    int            _columns;

    std::wstring     _germanAnthem;
    std::wstring     _chineseAnthem;
    std::wstring     _japaneseAnthem;
    std::wstring     _greekAnthem;
    std::wstring     _australianAnthem;
    std::wstring     _russianAnthem;
    std::wstring     _unitedKingdomAnthem;
    std::wstring     _czechAnthem;

private:

    void setBrowse(const bool enable,const wchar_t offset = 0);
};

//

GlutWindowUnicodeFontDemo::GlutWindowUnicodeFontDemo(const std::string &title,int width,int height,int x,int y,unsigned int displayMode)
: GlutWindow(title,width,height,x,y,displayMode),
  _info(_font,_viewport),
  _background(_texture,true),
  _browse(true),
  _update(true),
  _offset(0),
  _rows(0),
  _columns(0)
{
}

GlutWindowUnicodeFontDemo::~GlutWindowUnicodeFontDemo()
{
}

void
GlutWindowUnicodeFontDemo::OnOpen()
{
    _font.init(unicodeFont);
    _texture.init(backgroundTexture);

    _info.border() = false;
    _info.fadeColor().alpha() = 0.0;
    _info.shadow() = true;

    _background.color() = GltColor(0.8,0.8,0.9);

    glClearColor(0,0,0, 0.0);

    GlutMenu &sample = _leftButtonMenu.subMenu();
    sample.addEntry("Australian",    UFONT_SAMPLE_AUSTRALIAN);
    sample.addEntry("Chinese",       UFONT_SAMPLE_CHINESE);
    sample.addEntry("German",        UFONT_SAMPLE_GERMAN);
    sample.addEntry("Greek",         UFONT_SAMPLE_GREEK);
    sample.addEntry("Japanese",      UFONT_SAMPLE_JAPANESE);
    sample.addEntry("Russian",       UFONT_SAMPLE_RUSSIAN);
    sample.addEntry("United Kingdom",UFONT_SAMPLE_UNITEDKINGDOM);

    GlutMenu &view = _leftButtonMenu.subMenu();
    view.addEntry("Basic Latin"            , UFONT_SHOW_BASIC_LATIN);
    view.addEntry("Greek"                  , UFONT_SHOW_GREEK);
    view.addEntry("Cyrillic"               , UFONT_SHOW_CYRILLIC);
    view.addEntry("Greek"                  , UFONT_SHOW_GREEK);
    view.addEntry("Hebrew"                 , UFONT_SHOW_HEBREW);
    view.addEntry("Arabic"                 , UFONT_SHOW_ARABIC);
    view.addEntry("Thai"                   , UFONT_SHOW_THAI);
    view.addEntry("Lao"                    , UFONT_SHOW_LAO);
    view.addEntry("Currency Symbols"       , UFONT_SHOW_CURRENCY_SYMBOLS);
    view.addEntry("Mathematical Operators" , UFONT_SHOW_MATHEMATICAL_OPERATORS);
    view.addEntry("Dingbats"               , UFONT_SHOW_DINGBATS);
    view.addEntry("Hiragana"               , UFONT_SHOW_HIRAGANA);
    view.addEntry("Katakana"               , UFONT_SHOW_KATAKANA);
    view.addEntry("CJK Unified"            , UFONT_SHOW_CJK_UNIFIED_IDEOGRAPHS);
    view.addEntry("Hangul Syllables"       , UFONT_SHOW_HANGUL_SYLLABLES);

    _leftButtonMenu.addEntry("Sample",sample);
    _leftButtonMenu.addEntry("View"  ,view);
    _leftButtonMenu.addEntry("Close" ,MENU_CLOSE);
    _leftButtonMenu.attach();

    utf8decode(_germanAnthem,
        " \n" \
        " National Anthem of Germany\n" \
        " \n" \
        " Einigkeit und Recht und Freiheit\n" \
        " Für das Deutsche Vaterland.\n" \
        " Danach laßt uns alle streben,\n" \
        " Brüderlich mit Herz und Hand.\n" \
        " Einigkeit und Recht und Freiheit\n" \
        " Sind des Glückes Unterpfand.\n" \
        " Blüh' im Glanze dieses Glückes,\n" \
        " Blühe deutsches Vaterland.\n" \
        " \n" \
        " \n" \
        " Unity and right and freedom for the German fatherland;\n" \
        " Let us all pursue this purpose brotherly, with heart and hand.\n" \
        " Unity and right and freedom are the pledge of happiness.\n" \
        " Flourish in this blessing's glory, flourish, German fatherland."
        );

    utf8decode(_chineseAnthem,
        " \n" \
        " People's Republic of China\n" \
        " National Anthem\n" \
        " \n" \
        " 义勇军进行曲\n" \
        " \n" \
        " 歌曲：聂耳\n" \
        " 歌词：田汗\n" \
        " \n" \
        " 起来！不愿作奴隶的人们，\n" \
        " 把我们的血肉筑成我们新的长城。\n" \
        " 中华民族到了最危险的时候，\n" \
        " 每个人被迫着发出最后的吼声。\n" \
        " 起来！起来！起来！\n" \
        " 我们万众一心，冒着敌人的炮伙，\n" \
        " 前进！\n" \
        " 冒着敌人的炮伙，\n" \
        " 前进！前进！前进！进！"
        );

    utf8decode(_japaneseAnthem,
        " \n" \
        " Japanese National Anthem\n" \
        " \n" \
        " 君が代は\n" \
        " 千代に八千代に\n" \
        " さざれ石の\n" \
        " 巌となりて\n" \
        " 苔のむすまで\n" \
        " \n" \
        " Thousands of years of happy reign be thine\n" \
        " Rule on, my lord, till what are pebbles now\n" \
        " By age united to mighty rocks shall grow\n" \
        " Who's venerable sides the moss doth line."
        );

    utf8decode(_greekAnthem,
        " \n" \
        " National Anthem of Greece\n" \
        " \n" \
        " Ύμνος Εις Την Ελευθερίαν \n" \
        " του Διονυσίου Σολωμού\n" \
        " \n" \
        " Σε γνωρίζω από την κόψη\n" \
        " του σπαθιού την τρομερή,\n" \
        " σε γνωρίζω από την όψη\n" \
        " που με βία μετράει τη γη.\n" \
        " \n" \
        " Απ' τα κόκαλα βγαλμένη\n" \
        " των Ελλήνων τα ιερά,\n" \
        " και σαν πρώτα ανδρειωμένη,\n" \
        " χαίρε, ω χαίρε, Ελευθεριά!"
        );

    utf8decode(_australianAnthem,
        " \n" \
        " Australian National Anthem\n" \
        " \n" \
        " Australians all let us rejoice,\n" \
        " For we are young and free; \n" \
        " We've golden soil and wealth for toil, \n" \
        " Our home is girt by sea; \n" \
        " Our land abounds in Nature's gifts \n" \
        " Of beauty rich and rare; \n" \
        " In history's page, let every stage \n" \
        " Advance Australia fair! \n" \
        " In joyful strains then let us sing, \n" \
        " \"Advance Australia fair!\""
        );

    utf8decode(_russianAnthem,
        " \n" \
        " Russian National Anthem\n" \
        " \n" \
        " Россия - священная наша держава! \n" \
        " Россия - любимая наша страна! \n" \
        " Могучая воля, великая слава- \n" \
        " Твое достоянье на все времена \n" \
        " \n" \
        " ПРИПЕВ. \n" \
        "    Славься, Отечество наше свободное - \n" \
        "    Братских народов союз вековой! \n" \
        "    Предками данная мудрость народная. \n" \
        "    Славься, страна, мы гордимся тобой! "
        );

    utf8decode(_unitedKingdomAnthem,
        " \n" \
        " National Anthem of the United Kingdom\n" \
        " \n" \
        " God save our gracious Queen,\n" \
        " Long live our noble Queen,\n" \
        " God save the Queen!\n" \
        " Send her victorious,\n" \
        " Happy and glorious,\n" \
        " Long to reign over us,\n" \
        " God save the Queen!"
        );
}

void
GlutWindowUnicodeFontDemo::OnClose()
{
    _font.init(NULL);
    _texture.init(NULL);
}

void GlutWindowUnicodeFontDemo::OnDisplay()
{
   glClear(GL_COLOR_BUFFER_BIT);

    if (_browse && _update)
    {
        wstring &str = _info.text();
        wchar_t c = _offset;

        str = wstring();
        str.reserve((_columns+6)*_rows);

        for (int i=0; i<_rows; i++)
        {
            str += toHex( c>>12    );
            str += toHex((c>>8 )&15);
            str += toHex((c>>4 )&15);
            str += toHex( c     &15);
            str += ' ';

            for (int j=0; j<_columns; j++)
            {
                if (c=='\n' || c=='\0')
                {
                    str += ' ';
                    str += ' ';
                }
                else
                {
                    str += c;
                    for (int i = 16-_font.width(c); i>0; i-=8)
                        str += ' ';
                }

                str += ' ';
                c = (c+1)%0x10000;
            }

            str += '\n';

            _update = false;
       }
   }

    _background.draw();
    _info.draw();
}

void
GlutWindowUnicodeFontDemo::OnReshape(int w, int h)
{
    GlutWindow::OnReshape(w,h);

    w -= 2*(_info.margin()+_info.spacing());
    h -= 2*(_info.margin()+_info.spacing());

    _columns = w<40 ? 0 : (w-40)/24;
    _rows    = h/16;
    _update = true;
}

void
GlutWindowUnicodeFontDemo::OnKeyboard(unsigned char key, int x, int y)
{
    GlutWindow::OnKeyboard(key,x,y);

    switch (key)
    {
    default:
        break;
    }
}

void
GlutWindowUnicodeFontDemo::OnSpecial(int key, int x, int y)
{
    GlutWindow::OnSpecial(key,x,y);

    switch (key)
    {
    case GLUT_KEY_DOWN:      setBrowse(true,(_offset + _columns                )%0x10000); break;
    case GLUT_KEY_UP:        setBrowse(true,(_offset + 0x10000 - _columns      )%0x10000); break;
    case GLUT_KEY_PAGE_DOWN: setBrowse(true,(_offset + _columns*_rows          )%0x10000); break;
    case GLUT_KEY_PAGE_UP:   setBrowse(true,(_offset + 0x10000 - _columns*_rows)%0x10000); break;
    default:
        break;
    }

    postRedisplay();
}

void
GlutWindowUnicodeFontDemo::setBrowse(const bool enable,const wchar_t offset)
{
    if (enable)
    {
        _info.text() = wstring();
        _update = true;
        _offset = offset;
    }

    _browse = enable;
}

void
GlutWindowUnicodeFontDemo::OnMenu(int value)
{
    GlutWindow::OnMenu(value);

    switch (value)
    {
    case UFONT_SAMPLE_GERMAN:        _info.text() = _germanAnthem;        setBrowse(false); break;
    case UFONT_SAMPLE_GREEK:         _info.text() = _greekAnthem;         setBrowse(false); break;
    case UFONT_SAMPLE_CHINESE:       _info.text() = _chineseAnthem;       setBrowse(false); break;
    case UFONT_SAMPLE_JAPANESE:      _info.text() = _japaneseAnthem;      setBrowse(false); break;
    case UFONT_SAMPLE_AUSTRALIAN:    _info.text() = _australianAnthem;    setBrowse(false); break;
    case UFONT_SAMPLE_RUSSIAN:       _info.text() = _russianAnthem;       setBrowse(false); break;
    case UFONT_SAMPLE_UNITEDKINGDOM: _info.text() = _unitedKingdomAnthem; setBrowse(false); break;

    case UFONT_SHOW_BASIC_LATIN:                     setBrowse(true,0x0000); break;
    case UFONT_SHOW_LATIN1_SUPPLEMENT:               setBrowse(true,0x0080); break;
    case UFONT_SHOW_LATIN_EXTENDED_A:                setBrowse(true,0x0100); break;
    case UFONT_SHOW_LATIN_EXTENDED_B:                setBrowse(true,0x0180); break;
    case UFONT_SHOW_IPA_EXTENSIONS:                  setBrowse(true,0x0250); break;
    case UFONT_SHOW_SPACING_MODIFIER_LETTERS:        setBrowse(true,0x02B0); break;
    case UFONT_SHOW_COMBINING_DIACRITICAL_MARKS:     setBrowse(true,0x0300); break;
    case UFONT_SHOW_GREEK:                           setBrowse(true,0x0370); break;
    case UFONT_SHOW_CYRILLIC:                        setBrowse(true,0x0400); break;
    case UFONT_SHOW_ARMENIAN:                        setBrowse(true,0x0530); break;
    case UFONT_SHOW_HEBREW:                          setBrowse(true,0x0590); break;
    case UFONT_SHOW_ARABIC:                          setBrowse(true,0x0600); break;
    case UFONT_SHOW_THAI:                            setBrowse(true,0x0E00); break;
    case UFONT_SHOW_LAO:                             setBrowse(true,0x0E80); break;
    case UFONT_SHOW_GEORGIAN:                        setBrowse(true,0x10A0); break;
    case UFONT_SHOW_ETHIOPIC:                        setBrowse(true,0x1200); break;
    case UFONT_SHOW_LATIN_EXTENDED_ADDITIONAL:       setBrowse(true,0x1E00); break;
    case UFONT_SHOW_GREEK_EXTENDED:                  setBrowse(true,0x1F00); break;
    case UFONT_SHOW_GENERAL_PUNCTUATION:             setBrowse(true,0x2000); break;
    case UFONT_SHOW_SUPERSCRIPTS_AND_SUBSCRIPTS:     setBrowse(true,0x2070); break;
    case UFONT_SHOW_CURRENCY_SYMBOLS:                setBrowse(true,0x20A0); break;
    case UFONT_SHOW_COMBINING_MARKS_FOR_SYMBOLS:     setBrowse(true,0x20D0); break;
    case UFONT_SHOW_LETTERLIKE_SYMBOLS:              setBrowse(true,0x2100); break;
    case UFONT_SHOW_NUMBER_FORMS:                    setBrowse(true,0x2150); break;
    case UFONT_SHOW_ARROWS:                          setBrowse(true,0x2190); break;
    case UFONT_SHOW_MATHEMATICAL_OPERATORS:          setBrowse(true,0x2200); break;
    case UFONT_SHOW_MISCELLANEOUS_TECHNICAL:         setBrowse(true,0x2300); break;
    case UFONT_SHOW_CONTROL_PICTURES:                setBrowse(true,0x2400); break;
    case UFONT_SHOW_OPTICAL_CHARACTER_RECOGNITION:   setBrowse(true,0x2440); break;
    case UFONT_SHOW_ENCLOSED_ALPHANUMERICS:          setBrowse(true,0x2460); break;
    case UFONT_SHOW_BOX_DRAWING:                     setBrowse(true,0x2500); break;
    case UFONT_SHOW_BLOCK_ELEMENTS:                  setBrowse(true,0x2580); break;
    case UFONT_SHOW_GEOMETRIC_SHAPES:                setBrowse(true,0x25A0); break;
    case UFONT_SHOW_MISCELLANEOUS_SYMBOLS:           setBrowse(true,0x2600); break;
    case UFONT_SHOW_DINGBATS:                        setBrowse(true,0x2700); break;
    case UFONT_SHOW_BRAILLE_PATTERN_SYMBOLS:         setBrowse(true,0x2800); break;
    case UFONT_SHOW_CJK_SYMBOLS_AND_PUNCTUATION:     setBrowse(true,0x3000); break;
    case UFONT_SHOW_HIRAGANA:                        setBrowse(true,0x3040); break;
    case UFONT_SHOW_KATAKANA:                        setBrowse(true,0x30A0); break;
    case UFONT_SHOW_BOPOMOFO:                        setBrowse(true,0x3100); break;
    case UFONT_SHOW_HANGUL_COMPATIBILITY_JAMO:       setBrowse(true,0x3130); break;
    case UFONT_SHOW_ENCLOSED_CJK_LETTERS_AND_MONTHS: setBrowse(true,0x3200); break;
    case UFONT_SHOW_CJK_COMPATIBILITY:               setBrowse(true,0x3300); break;
    case UFONT_SHOW_CJK_UNIFIED_IDEOGRAPHS:          setBrowse(true,0x4E00); break;
    case UFONT_SHOW_HANGUL_SYLLABLES:                setBrowse(true,0xAC00); break;
    case UFONT_SHOW_CJK_COMPATIBILITY_IDEOGRAPHS:    setBrowse(true,0xF900); break;
    case UFONT_SHOW_ALPHABETIC_PRESENTATION_FORMS:   setBrowse(true,0xFB00); break;
    case UFONT_SHOW_ARABIC_PRESENTATION_FORMS_A:     setBrowse(true,0xFB50); break;
    case UFONT_SHOW_COMBINING_HALF_MARKS:            setBrowse(true,0xFE20); break;
    case UFONT_SHOW_CJK_COMPATIBILITY_FORMS:         setBrowse(true,0xFE30); break;
    case UFONT_SHOW_SMALL_FORM_VARIANTS:             setBrowse(true,0xFE50); break;
    case UFONT_SHOW_ARABIC_PRESENTATION_FORMS_B:     setBrowse(true,0xFE70); break;
    case UFONT_SHOW_HALFWIDTH_AND_FULLWIDTH_FORMS:   setBrowse(true,0xFF00); break;
    case UFONT_SHOW_SPECIALS:                        setBrowse(true,0xFFF0); break;

    }

    postRedisplay();
}

bool
GlutWindowUnicodeFontDemo::loadUnicodeText(const string &filename)
{
    ifstream is(filename.c_str(),ios::binary|ios::in);
    readUnicodeStream(is,_info.text());
    return true;
}

#endif

//

bool GlutMain(const std::vector<std::string> &arg)
{
    cout << endl;
    cout << "unifonte" << endl;
    cout << endl;
    cout << "GNU Unicode Font Demo." << endl;
    cout << "(C) 2001 Nigel Stewart (nigels@nigels.com)" << endl;
    cout << "Source code available under terms of LGPL." << endl;
    cout << "For updates, source code and information:" << endl;
    cout << "http://www.nigels.com/glt/" << endl;
    cout << endl;
    cout << "Usage: unifont [uft8demotext.txt]" << endl;
    cout << endl;
    cout << "Instructions:" << endl;
    cout << "\tArrow up/down"                            << endl;
    cout << "\tPage  up/down - scroll through the font"  << endl;
    cout << "\tLeft Mouse    - menu"                     << endl;
    cout << "\tTAB           - toggle full screen"       << endl;
    cout << "\tESC           - exit"                     << endl;
    cout << endl;

#ifdef GLT_UNICODE

    static GlutWindowUnicodeFontDemo *main = new GlutWindowUnicodeFontDemo("GNU Unicode Font Demo",560,320,10,10);

    if (arg.size()>1)
        main->loadUnicodeText(arg[1]);

    main->open();

    return true;
#else

    cout << "GLT not compiled with unicode support.  Exiting" << endl;
    return false;
#endif
}

