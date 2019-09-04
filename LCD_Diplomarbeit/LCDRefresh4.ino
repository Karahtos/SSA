void LCDRefresh4()
{
  lcd.clear();
  lcd.print("Soda");
  lcd.setCursor(0, 1);
  lcd.print(g4);
  lcd.setCursor(3, 1);
  lcd.print("ml");
  lcd.setCursor(2, 1);

}

