// 演習課題4: 圧電スピーカー使用，入力した時間後に音鳴らす

// defineはコンパイル時にマクロ変換される
#define BZ 9   // 圧電スピーカー接続ピン

/**
 * 関数名: setup
 * 引数: なし
 * 処理: 各初期設定のため初回のみ実行
 * 返り値: なし
 */
void setup () {
    // put your setup code here, to run once:

    pinMode ( BZ, OUTPUT );  // 圧電スピーカー接続ピン
    Serial.begin ( 9600 );   // シリアル通信の初期化
}

int f = 440;     // 再生する周波数[Hz]
int playTime = 500;  // 再生している時間[ms]

/**
 * 関数名: loop
 * 引数: なし
 * 処理: 無限ループ．任意の周波数で音を交互に鳴らしサイレンを鳴らす
 * 返り値: なし
 */
void loop () {
    // put your main code here, to run repeatedly:
    // tone関数は3, 11番ピンの出力を妨げる

    int inputTime = Serial.read ();           // シリアルモニタから入力を読み取る

    // 入力を読み取れた場合
    if ( inputTime != -1 ) {
        int t = inputTime - 0x30;         // 入力した時間[sec]

        // 0-9秒の範囲であるか
        if ( -1 < t && t < 10 ) {
            // 表示
            Serial.print ( t );           // 入力した秒数
            Serial.println ( " 秒待機" );  // 改行あり

            delay ( t * 1000 );           // 入力された時間待機[sec]
            tone ( BZ, f, playTime );     // 音再生
            delay ( playTime );           // 再生されている時間遅延[ms]
        }
    }
}
