## 数値解析学1 大レポート課題

未来ロボティクス学科セメスター4 数値解析学1で作った言語処理のプログラムです。

## Download

適当なところにクローンしてから、コンパイルしてください

```
git clone https://github.com/hide4096/LanguageProcessing.git
cd LanguageProcessing
gcc problem1_prepare.c -lm
```

## Description

### problem1_prepare

- 読み込んだ文章から、数字、アルファベット、空白、改行以外の文字を空白に変換します。また、アルファベットは小文字に変換されます。

### problem2_frequece

- 文章を読みこんで、アルファベット、空白、改行文字の数をカウントします。また、各々の文字を数で降順に並べて表示します。


### problem3_frequece

- problem2_frequeceに加えて、二つ組、三つ組の文字列をカウントして降順にして出力します。

### problem4

- problem2_frequeceの処理によって各々の文字の出現確率を計算し、それに応じて第一近似で文章を生成します

### problem4_simple_*

- 簡便法によってそれぞれ第一、第二、第三近似で文章を生成します


## License

- このソフトウェアパッケージは，3条項BSDライセンスの下，再頒布および使用が許可されます．

- © 2022 Aso Hidetoshi
