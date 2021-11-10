/*
 * Display.c
 *
 *  Created on: Jan 5, 2017
 *      Author: ruben
 */

#include "ILI9340.h"
#include <string.h>

void delay (unsigned long time)
{
	unsigned long i;
	for (i = 0; i <= time ; i++ );

	return;
}

void SPI_Init(void){
	SSP_ConfigFormat ssp_format;

	GPIOs_SSP_Init();
	Board_SSP_Init(LPC_SSP0);
	Chip_SSP_Init(LPC_SSP0);
	Chip_SSP_SetBitRate(LPC_SSP0,40000000); // Default es de 100000, max testeado 40000000
	ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI;
	ssp_format.bits = SSP_BITS_8;
	ssp_format.clockMode = SSP_CLOCK_CPHA0_CPOL0;
	Chip_SSP_SetFormat(LPC_SSP0, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode);
	Chip_SSP_Enable(LPC_SSP0);

	NVIC_EnableIRQ(SSP1_IRQn);
	Chip_SSP_SetMaster(LPC_SSP0, 1);
}

void GPIOs_SSP_Init(void)
{
	Chip_IOCON_PinMux(LPC_IOCON, RST_SPP, IOCON_MODE_PULLDOWN, IOCON_FUNC0);
	Chip_IOCON_PinMux(LPC_IOCON, DC_SPP , IOCON_MODE_PULLDOWN, IOCON_FUNC0);
	Chip_IOCON_PinMux(LPC_IOCON, CS_SPP , IOCON_MODE_PULLDOWN, IOCON_FUNC0);

	Chip_GPIO_SetPinDIROutput(LPCP0, RST_SPP);
	Chip_GPIO_SetPinDIROutput(LPCP0, DC_SPP);
	Chip_GPIO_SetPinDIROutput(LPCP0, CS_SPP);

	Chip_GPIO_WritePortBit(LPCP0,DC_SPP , FALSE);
	Chip_GPIO_WritePortBit(LPCP0,RST_SPP, FALSE);
	Chip_GPIO_WritePortBit(LPCP0,CS_SPP , FALSE);
}

void TFT_Init(){

  Chip_GPIO_WritePortBit (LPCP0,RST_SPP, TRUE);
  delay(5);
  Chip_GPIO_WritePortBit (LPCP0,RST_SPP, FALSE);
  delay(20);
  Chip_GPIO_WritePortBit (LPCP0,RST_SPP, TRUE);
  delay(150);


  writecommand(0xEF);
  delay(500);
  writedata(0x03);
  writedata(0x80);
  writedata(0x02);

  writecommand(0xCF);
  delay(500);
  writedata(0x00);
  writedata(0XC1);
  writedata(0X30);

  writecommand(0xED);
  delay(500);
  writedata(0x64);
  writedata(0x03);
  writedata(0X12);
  writedata(0X81);

  writecommand(0xE8);
  delay(500);
  writedata(0x85);
  writedata(0x00);
  writedata(0x78);

  writecommand(0xCB);
  delay(500);
  writedata(0x39);
  writedata(0x2C);
  writedata(0x00);
  writedata(0x34);
  writedata(0x02);

  writecommand(0xF7);
  delay(500);
  writedata(0x20);

  writecommand(0xEA);
  delay(500);
  writedata(0x00);
  writedata(0x00);

  writecommand(ILI9340_PWCTR1);    //Power control
  delay(500);
  writedata(0x23);   //VRH[5:0]

  writecommand(ILI9340_PWCTR2);    //Power control
  delay(500);
  writedata(0x10);   //SAP[2:0];BT[3:0]

  writecommand(ILI9340_VMCTR1);    //VCM control
  delay(500);
  writedata(0x3e); //�Աȶȵ���
  writedata(0x28);

  writecommand(ILI9340_VMCTR2);    //VCM control2
  delay(500);
  writedata(0x86);  //--

  writecommand(ILI9340_MADCTL);    // Memory Access Control
  delay(500);
  writedata(ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);

  writecommand(ILI9340_PIXFMT);
  delay(500);
  writedata(0x55);

  writecommand(ILI9340_FRMCTR1);
  delay(500);
  writedata(0x00);
  writedata(0x18);

  writecommand(ILI9340_DFUNCTR);    // Display Function Control
  delay(500);
  writedata(0x08);
  writedata(0x82);
  writedata(0x27);

  writecommand(0xF2);    // 3Gamma Function Disable
  delay(500);
  writedata(0x00);

  writecommand(ILI9340_GAMMASET);    //Gamma curve selected
  delay(500);
  writedata(0x01);

  writecommand(ILI9340_GMCTRP1);    //Set Gamma
  delay(500);
  writedata(0x0F);
  writedata(0x31);
  writedata(0x2B);
  writedata(0x0C);
  writedata(0x0E);
  writedata(0x08);
  writedata(0x4E);
  writedata(0xF1);
  writedata(0x37);
  writedata(0x07);
  writedata(0x10);
  writedata(0x03);
  writedata(0x0E);
  writedata(0x09);
  writedata(0x00);

  writecommand(ILI9340_GMCTRN1);    //Set Gamma
  delay(500);
  writedata(0x00);
  writedata(0x0E);
  writedata(0x14);
  writedata(0x03);
  writedata(0x11);
  writedata(0x07);
  writedata(0x31);
  writedata(0xC1);
  writedata(0x48);
  writedata(0x08);
  writedata(0x0F);
  writedata(0x0C);
  writedata(0x31);
  writedata(0x36);
  writedata(0x0F);

  writecommand(ILI9340_SLPOUT);    //Exit Sleep
  //delay(500);
  writecommand(ILI9340_DISPON);    //Display on


    _width    = ILI9340_TFTWIDTH;
    _height   = ILI9340_TFTHEIGHT;
    gfxFont=NULL;
    wrap=TRUE;

	//  setRotation(3);//modo landscape
	//  fillScreen(ILI9340_BLACK);
	//  fillRect(0,120,320,100,ILI9340_BLACK);


}
void writecommand(uint8_t valor)
{
	Chip_GPIO_WritePortBit (LPCP0,DC_SPP, FALSE);
	Chip_GPIO_WritePortBit (LPCP0,CS_SPP, FALSE);
	//delay(500);
	spiwrite(valor);
	Chip_GPIO_WritePortBit (LPCP0,CS_SPP, TRUE);
  }
void writedata(uint8_t valor)
{
	Chip_GPIO_WritePortBit (LPCP0,DC_SPP, TRUE);
	Chip_GPIO_WritePortBit (LPCP0,CS_SPP, FALSE);
//	delay(5);
	spiwrite(valor);
	Chip_GPIO_WritePortBit (LPCP0,CS_SPP, TRUE);
  }


void fillScreen(uint16_t color) {
  fillRect(0, 0,  _width, _height, color);
}
// fill a rectangle
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,  uint16_t color)
{

  // rudimentary clipping (drawChar w/big text requires this)
  if((x >= _width) || (y >= _height)) return;
  if((x + w - 1) >= _width)  w = _width  - x;
  if((y + h - 1) >= _height) h = _height - y;

  setAddrWindow((uint16_t)x,(uint16_t) y,(uint16_t) (x+w-1),(uint16_t)( y+h-1));

  uint8_t hi = color >> 8, lo = color;

  Chip_GPIO_WritePortBit (LPCP0,DC_SPP, TRUE);
	Chip_GPIO_WritePortBit (LPCP0,CS_SPP, FALSE);
  for(y=h; y>0; y--) {
    for(x=w; x>0; x--) {
      spiwrite(hi);
      spiwrite(lo);
    }
  }
  //digitalWrite(_cs, HIGH);
	Chip_GPIO_WritePortBit (LPCP0,CS_SPP, TRUE);
}

void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{

  writecommand(ILI9340_CASET); // Column addr set
  writedata(x0 >> 8);
  writedata(x0 & 0xFF);     // XSTART
  writedata(x1 >> 8);
  writedata(x1 & 0xFF);     // XEND

  writecommand(ILI9340_PASET); // Row addr set
  writedata(y0>>8);
  writedata(y0);     // YSTART
  writedata(y1>>8);
  writedata(y1);     // YEND

  writecommand(ILI9340_RAMWR); // write to RAM
}

void spiwrite(uint8_t c)
{
	   Chip_SSP_ClearIntPending(LPC_SSP, SSP_INT_CLEAR_BITMASK);
	   while(!Chip_SSP_GetStatus(LPC_SSP, SSP_STAT_TNF));
	  // Chip_GPIO_WritePortBit (LPCP0,CS_SPP, 0);
	   Chip_SSP_SendFrame(LPC_SSP, c);
		while(Chip_SSP_GetStatus(LPC_SSP, SSP_STAT_RNE) == SET)
		Chip_SSP_ReceiveFrame(LPC_SSP);
		//Chip_GPIO_WritePortBit (LPCP0,CS_SPP, 1);
}

void setRotation(uint8_t m) {

	  writecommand(ILI9340_MADCTL);
	  rotation = m % 4; // can't be higher than 3
	  switch (rotation) {
	   case 0:
	     writedata(ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);
	     _width  = ILI9340_TFTWIDTH;
	     _height = ILI9340_TFTHEIGHT;
	     break;
	   case 1:
	     writedata(ILI9340_MADCTL_MV | ILI9340_MADCTL_BGR);
	     _width  = ILI9340_TFTHEIGHT;
	     _height = ILI9340_TFTWIDTH;
	     break;
	  case 2:
	    writedata(ILI9340_MADCTL_MY | ILI9340_MADCTL_BGR);
	     _width  = ILI9340_TFTWIDTH;
	     _height = ILI9340_TFTHEIGHT;
	    break;
	   case 3:
	     writedata(ILI9340_MADCTL_MV | ILI9340_MADCTL_MY | ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);
	     _width  = ILI9340_TFTHEIGHT;
	     _height = ILI9340_TFTWIDTH;
	     break;
	  }
}
void testFillScreen()
{
  fillScreen(ILI9340_BLACK);
  fillScreen(ILI9340_RED);
  fillScreen(ILI9340_GREEN);
  fillScreen(ILI9340_BLUE);
  fillScreen(ILI9340_BLACK);
}

void testText(void)
{
	  fillScreen(ILI9340_BLACK);
	  setCursor(0, 0);
	  setTextColor(ILI9340_WHITE);
	  setTextSize(1);
	  println("Hello World!");
	  setTextColor(ILI9340_YELLOW);
	  println("\n");
	  setTextSize(2);
	  printn(123456);//recordar q uso otra funcion para numeros
	  setTextColor(ILI9340_RED);
	  setTextSize(3);
	  setTextColor(ILI9340_GREEN);
	  println("\n");
	  setTextSize(5);
	  println("Groop");
	  println("\n");
	  setTextSize(2);
	  println("I implore thee,");
	  println("\n");
	  setTextSize(1);
	  println("my foonting turlingdromes.");
	  println("And hooptiously drangle me");
	  println("with crinkly bindlewurdles,");
	  println("Or I will rend thee");
	  println("in the gobberwarts");
	  println("with my blurglecruncheon,");
	  println("see if I don't!");
	  // el hecho de que corte la linea y lo escriba abajo esta configurado con el bool  wrap
}

void println( char c[])
{
	uint8_t contador=0,aux=strlen(c);

	while(contador<=aux)
		{
			write(c[contador]);
			contador++;
		}
	//write(sizeof(c)+48);
}
void printfloat( char *number)
{
	int i;
	  for (i = 0; i < 3 ; i++)
	  {
		  if (number[i] <= '9' && number[i] >= '0')
			  write(number[i]);
		  else
			  break;

	  }
}

void printn( int number)
{
	int num[3],i;
	num[2]=number%10;
	number/=10;
	num[1]=number%10;
	number/=10;
	num[0]=number%10;
	for(i=0;i<3;i++)
		write(num[i]+48);
}



void setCursor(int16_t x, int16_t y) {
  cursor_x = x;
  cursor_y = y;
}


void setTextColor(uint16_t c) {
  // For 'transparent' background, we'll set the bg
  // to the same as fg instead of using a flag
  textcolor = textbgcolor = c;
}

void setTextSize(uint8_t s) {
  textsize = (s > 0) ? s : 1;
}

//LE SAQUE POR MI CUENTA LA PARTE DEL FRONT PERSONALIZADO
void write(uint8_t c) {

  if(!gfxFont) { // 'Classic' built-in font

    if(c == '\n') {
      cursor_y += textsize*8;
      cursor_x  = 0;
    } else if(c == '\r') {
      // skip em
    } else {
      if(wrap && ((cursor_x + textsize * 6) >= _width)) { // Heading off edge?
        cursor_x  = 0;            // Reset x to zero
        cursor_y += textsize * 8; // Advance y one line
      }
      drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
      cursor_x += textsize * 6;
    }

  } else { // Custom font
/*
    if(c == '\n') {
      cursor_x  = 0;
      cursor_y += (int16_t)textsize *
                  (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
    } else if(c != '\r') {
      uint8_t first = pgm_read_byte(&gfxFont->first);
      if((c >= first) && (c <= (uint8_t)pgm_read_byte(&gfxFont->last))) {
        uint8_t   c2    = c - pgm_read_byte(&gfxFont->first);
        GFXglyph *glyph = &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c2]);
        uint8_t   w     = pgm_read_byte(&glyph->width),
                  h     = pgm_read_byte(&glyph->height);
        if((w > 0) && (h > 0)) { // Is there an associated bitmap?
          int16_t xo = (int8_t)pgm_read_byte(&glyph->xOffset); // sic
          if(wrap && ((cursor_x + textsize * (xo + w)) >= _width)) {
            // Drawing character would go off right edge; wrap to new line
            cursor_x  = 0;
            cursor_y += (int16_t)textsize *
                        (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
          }
          drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
        }
        cursor_x += pgm_read_byte(&glyph->xAdvance) * (int16_t)textsize;
      }
    }
    */
  }
}

// Draw a character
//LE SAQUE POR MI CUENTA LA PARTE DEL FRONT PERSONALIZADO
void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {
	int8_t i,j;
  if(!gfxFont) { // 'Classic' built-in font

    if((x >= _width)            || // Clip right
       (y >= _height)           || // Clip bottom
       ((x + 6 * size - 1) < 0) || // Clip left
       ((y + 8 * size - 1) < 0))   // Clip top
      return;

    if(!_cp437 && (c >= 176)) c++; // Handle 'classic' charset behavior

    for( i=0; i<6; i++ ) {
      uint8_t line;
      if(i < 5) line = pgm_read_byte(font+(c*5)+i);
      else      line = 0x0;
      for( j=0; j<8; j++, line >>= 1) {
        if(line & 0x1) {
          if(size == 1) drawPixel(x+i, y+j, color);
          else          fillRect(x+(i*size), y+(j*size), size, size, color);
        } else if(bg != color) {
          if(size == 1) drawPixel(x+i, y+j, bg);
          else          fillRect(x+i*size, y+j*size, size, size, bg);
        }
      }
    }

  } else { // Custom font
/*
    // Character is assumed previously filtered by write() to eliminate
    // newlines, returns, non-printable characters, etc.  Calling drawChar()
    // directly with 'bad' characters of font may cause mayhem!

    c -= pgm_read_byte(&gfxFont->first);
    GFXglyph *glyph  = &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c]);
    uint8_t  *bitmap = (uint8_t *)pgm_read_pointer(&gfxFont->bitmap);

    uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
    uint8_t  w  = pgm_read_byte(&glyph->width),
             h  = pgm_read_byte(&glyph->height),
             xa = pgm_read_byte(&glyph->xAdvance);
    int8_t   xo = pgm_read_byte(&glyph->xOffset),
             yo = pgm_read_byte(&glyph->yOffset);
    uint8_t  xx, yy, bits, bit = 0;
    int16_t  xo16, yo16;

    if(size > 1) {
      xo16 = xo;
      yo16 = yo;
    }

    // Todo: Add character clipping here

    // NOTE: THERE IS NO 'BACKGROUND' COLOR OPTION ON CUSTOM FONTS.
    // THIS IS ON PURPOSE AND BY DESIGN.  The background color feature
    // has typically been used with the 'classic' font to overwrite old
    // screen contents with new data.  This ONLY works because the
    // characters are a uniform size; it's not a sensible thing to do with
    // proportionally-spaced fonts with glyphs of varying sizes (and that
    // may overlap).  To replace previously-drawn text when using a custom
    // font, use the getTextBounds() function to determine the smallest
    // rectangle encompassing a string, erase the area with fillRect(),
    // then draw new text.  This WILL infortunately 'blink' the text, but
    // is unavoidable.  Drawing 'background' pixels will NOT fix this,
    // only creates a new set of problems.  Have an idea to work around
    // this (a canvas object type for MCUs that can afford the RAM and
    // displays supporting setAddrWindow() and pushColors()), but haven't
    // implemented this yet.

    for(yy=0; yy<h; yy++) {
      for(xx=0; xx<w; xx++) {
        if(!(bit++ & 7)) {
          bits = pgm_read_byte(&bitmap[bo++]);
        }
        if(bits & 0x80) {
          if(size == 1) {
            drawPixel(x+xo+xx, y+yo+yy, color);
          } else {
            fillRect(x+(xo16+xx)*size, y+(yo16+yy)*size, size, size, color);
          }
        }
        bits <<= 1;
      }
    }
    */
  } // End classic vs custom font
}


void drawPixel(int16_t x, int16_t y, uint16_t color) {

  if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) return;

  setAddrWindow(x,y,x+1,y+1);

	Chip_GPIO_WritePortBit (LPCP0,DC_SPP, TRUE);
	Chip_GPIO_WritePortBit (LPCP0,CS_SPP, FALSE);

  spiwrite(color >> 8);
  spiwrite(color);

	Chip_GPIO_WritePortBit (LPCP0,CS_SPP, TRUE);
}



void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{

  // Rudimentary clipping
  if((x >= _width) || (y >= _height)) return;

  if((y+h-1) >= _height)
    h = _height-y;

  setAddrWindow(x, y, x, y+h-1);

  uint8_t hi = color >> 8, lo = color;
	Chip_GPIO_WritePortBit (LPCP0,DC_SPP, TRUE);
	Chip_GPIO_WritePortBit (LPCP0,CS_SPP, FALSE);


  while (h--) {
    spiwrite(hi);
    spiwrite(lo);
  }
	Chip_GPIO_WritePortBit (LPCP0,CS_SPP, TRUE);
}


void drawFastHLine(int16_t x, int16_t y, int16_t w,  uint16_t color)
{

  // Rudimentary clipping
  if((x >= _width) || (y >= _height)) return;
  if((x+w-1) >= _width)  w = _width-x;
  setAddrWindow(x, y, x+w-1, y);

  uint8_t hi = color >> 8, lo = color;
	Chip_GPIO_WritePortBit (LPCP0,DC_SPP, TRUE);
	Chip_GPIO_WritePortBit (LPCP0,CS_SPP, FALSE);

  //digitalWrite(_dc, HIGH);
  //digitalWrite(_cs, LOW);
  while (w--) {
    spiwrite(hi);
    spiwrite(lo);
  }
	Chip_GPIO_WritePortBit (LPCP0,CS_SPP, TRUE);
}

// Bresenham's algorithm - thx wikpedia
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
if (steep) {
  _swap_int16_t(x0, y0);
  _swap_int16_t(x1, y1);
}

if (x0 > x1) {
  _swap_int16_t(x0, x1);
  _swap_int16_t(y0, y1);
}

int16_t dx, dy;
dx = x1 - x0;
dy = abs(y1 - y0);

int16_t err = dx / 2;
int16_t ystep;

if (y0 < y1) {
  ystep = 1;
} else {
  ystep = -1;
}

for (; x0<=x1; x0++) {
  if (steep) {
    drawPixel(y0, x0, color);
  } else {
    drawPixel(x0, y0, color);
  }
  err -= dy;
  if (err < 0) {
    y0 += ystep;
    err += dx;
  }
}
}


void testLines(uint16_t color) {

  int           x1, y1, x2, y2,
                w = width(),
                h = height();

  fillScreen(ILI9340_BLACK);

  x1 = y1 = 0;
  y2    = h - 1;

  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);


  fillScreen(ILI9340_BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;

  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);


  fillScreen(ILI9340_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;

  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    =    w-1;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);


  fillScreen(ILI9340_BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;

  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);

}

int16_t width(void)  {
  return _width;
}

int16_t height(void)  {
  return _height;
}

void testFastLines(uint16_t color1, uint16_t color2) {

  int           x, y, w = width(), h = height();

  fillScreen(ILI9340_BLACK);

  for(y=0; y<h; y+=5) drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) drawFastVLine(x, 0, h, color2);

}

void testRects(uint16_t color) {
  int           n, i, i2,
                cx = width()  / 2,
                cy = height() / 2;

  fillScreen(ILI9340_BLACK);
  n     = min(width(), height());
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    drawRect(cx-i2, cy-i2, i, i, color);
  }
}
void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  drawFastHLine(x, y, w, color);
  drawFastHLine(x, y+h-1, w, color);
  drawFastVLine(x, y, h, color);
  drawFastVLine(x+w-1, y, h, color);
}

void testFilledRects(uint16_t color1, uint16_t color2) {
  int           n, i, i2,
                cx = width()  / 2 - 1,
                cy = height() / 2 - 1;

  fillScreen(ILI9340_BLACK);
  n = min(width(), height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    fillRect(cx-i2, cy-i2, i, i, color1);
    // Outlines are not included in timing results
    drawRect(cx-i2, cy-i2, i, i, color2);
  }

}


void testFilledCircles(uint8_t radius, uint16_t color) {
  int x, y, w = width(), h = height(), r2 = radius * 2;

  fillScreen(ILI9340_BLACK);
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      fillCircle(x, y, radius, color);
    }
  }
}

void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  drawFastVLine(x0, y0-r, 2*r+1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}
// Used to do circles and roundrects
void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}

void testCircles(uint8_t radius, uint16_t color) {
  int           x, y, r2 = radius * 2,
                w = width()  + radius,
                h = height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      drawCircle(x, y, radius, color);
    }
  }
}

// Draw a circle outline
void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawPixel(x0  , y0+r, color);
  drawPixel(x0  , y0-r, color);
  drawPixel(x0+r, y0  , color);
  drawPixel(x0-r, y0  , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}

void testTriangles() {

  int           n, i, cx = width()  / 2 - 1,
                      cy = height() / 2 - 1;

  fillScreen(ILI9340_BLACK);
  n     = min(cx, cy);
  for(i=0; i<n; i+=5) {
    drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      Color565(0, 0, i));
  }
}

// Draw a triangle
void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}
void testFilledTriangles() {
  int           i, cx = width()  / 2 - 1,
                   cy = height() / 2 - 1;

  fillScreen(ILI9340_BLACK);
  for(i=min(cx,cy); i>10; i-=5) {
    fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,Color565(0, i, i));
    drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      Color565(i, i, 0));
  }
}

// Fill a triangle
void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {

  int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
  }
  if (y1 > y2) {
    _swap_int16_t(y2, y1); _swap_int16_t(x2, x1);
  }
  if (y0 > y1) {
    _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    drawFastHLine(a, y0, b-a+1, color);
    return;
  }

  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
  int32_t
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) _swap_int16_t(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) _swap_int16_t(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }
}
// Pass 8-bit (each) R,G,B, get back 16-bit packed color
uint16_t Color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void testRoundRects() {
  int           w, i, i2,
                cx = width()  / 2 - 1,
                cy = height() / 2 - 1;

  fillScreen(ILI9340_BLACK);
  w     = min(width(), height());
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    drawRoundRect(cx-i2, cy-i2, i, i, i/8, Color565(i, 0, 0));
  }
}

// Draw a rounded rectangle
void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
  // smarter version
  drawFastHLine(x+r  , y    , w-2*r, color); // Top
  drawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
  drawFastVLine(x    , y+r  , h-2*r, color); // Left
  drawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
  // draw four corners
  drawCircleHelper(x+r    , y+r    , r, 1, color);
  drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
  drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}


void drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 + y, y0 + x, color);
    }
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, color);
      drawPixel(x0 - x, y0 - y, color);
    }
  }
}

void testFilledRoundRects() {
  int           i, i2,
                cx = width()  / 2 - 1,
                cy = height() / 2 - 1;

  fillScreen(ILI9340_BLACK);
  for(i=min(width(), height()); i>20; i-=6) {
    i2 = i / 2;
    fillRoundRect(cx-i2, cy-i2, i, i, i/8, Color565(0, i, 0));
  }
}

// Fill a rounded rectangle
void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
  // smarter version
  fillRect(x+r, y, w-2*r, h, color);

  // draw four corners
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}


void drawBitmap(int16_t x, int16_t y,
 const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++ ) {
            if(i & 7) byte <<= 1;
            else      byte   = bitmap[j * byteWidth + i / 8];
            if(byte & 0x80) drawPixel(x+i, y, color);
        }
    }
}


void off_wifi (void)
{
      //OFF SELECCIONADO

      fillRect(60,17+50,83,26, ILI9340_WHITE);

	  drawFastHLine(60, 18+50 , 83, ILI9340_BLUE);
	  drawFastHLine(60, 18+24+50 , 83, ILI9340_BLUE);
	  drawFastVLine(60, 18+50, 24, ILI9340_BLUE);
      drawFastVLine(60+83, 18+50, 24, ILI9340_BLUE);

      fillRect(100,18+50,43,24,ILI9340_BLUE);
	  setTextSize(2);
	  setTextColor(ILI9340_BLACK);setCursor(69, 24+50);println("ON");
	  setTextColor(ILI9340_WHITE);setCursor(105, 24+50);println("OFF");
}

      //ON SELECCIONADO
void on_wifi(void)
{
      fillRect(60,17+50,83,26, ILI9340_WHITE);

	  drawFastHLine(60, 18+50 , 83, ILI9340_BLUE);
	  drawFastHLine(60, 18+24+50 , 83, ILI9340_BLUE);
	  drawFastVLine(60, 18+50, 24, ILI9340_BLUE);
      drawFastVLine(60+83, 18+50, 24, ILI9340_BLUE);

      fillRect(60,18+50,43,24,ILI9340_BLUE);
	  setTextSize(2);
	  setTextColor(ILI9340_WHITE);setCursor(69, 24+50);println("ON");
	  setTextColor(ILI9340_BLACK);setCursor(105, 24+50);println("OFF");
}

//OFF SELECCIONADO
void off_bt(void)
	{
	fillRect(60,17,83,26, ILI9340_WHITE);

	drawFastHLine(60, 18 , 83, ILI9340_BLUE);
	drawFastHLine(60, 18+24 , 83, ILI9340_BLUE);
	drawFastVLine(60, 18, 24, ILI9340_BLUE);
	drawFastVLine(60+83, 18, 24, ILI9340_BLUE);

	fillRect(100+1,18+1,43,24-1,ILI9340_BLUE);
	setTextSize(2);
	setTextColor(ILI9340_BLACK);setCursor(69, 24);println("ON");
	setTextColor(ILI9340_WHITE);setCursor(105, 24);println("OFF");
	}


void on_bt(void)
	{
	//ON SELECCIONADO
	fillRect(60,17,83,26, ILI9340_WHITE);

	drawFastHLine(60, 18 , 83, ILI9340_BLUE);
	drawFastHLine(60, 18+24 , 83, ILI9340_BLUE);
	drawFastVLine(60, 18, 24, ILI9340_BLUE);
	drawFastVLine(60+83, 18, 24, ILI9340_BLUE);

	fillRect(60,18,43,24, ILI9340_BLUE);
	setTextSize(2);
	setTextColor(ILI9340_WHITE);setCursor(69, 24);println("ON");
	setTextColor(ILI9340_BLACK);setCursor(105, 24);println("OFF");
	}

void grilla(void)
{
	  uint8_t i = 0;

      drawFastVLine(159, 100,139,ILI9340_GREEN);
	  drawFastHLine(0, 169, 319, ILI9340_GREEN);

	  for (i = 0; i < 6 ; i ++)
	  {
		 if ( i != 3)
			 drawFastHLine(154, 99+(23*i) ,10,ILI9340_GREEN);
	  }

	  for (i = 0; i < 4 ; i ++)
			 drawFastVLine(32+(32*i), 164,10,ILI9340_GREEN);

	  for (i = 0; i < 4 ; i ++)
			 drawFastVLine(191+(32*i), 164,10,ILI9340_GREEN);
}

//MODO ACTIVO
void modo_activo(void)
{
setTextColor(ILI9340_WHITE);setTextSize(2);setCursor(205,77);println("INACTIVO");
setTextColor(ILI9340_RED);setTextSize(2);setCursor(210,77);println("ACTIVO");
}

void modo_inactivo(void)
{
setTextColor(ILI9340_WHITE);setTextSize(2);setCursor(210,77);println("ACTIVO");
setTextColor(ILI9340_MAGENTA);setTextSize(2);setCursor(205,77);println("INACTIVO");
}

void version (void)
{
setTextColor(ILI9340_WHITE);setTextSize(1);setCursor(293,230);println("v1.0");
}

void ppm_graph (char *num)
{
	static char valor_en_pantalla[3];

    setTextColor(ILI9340_WHITE);setTextSize(2);setCursor(280,24);printfloat(valor_en_pantalla);
    setTextColor(ILI9340_BLACK);setTextSize(2);setCursor(280,24);printfloat(num);

    strcpy(valor_en_pantalla , num);


}
