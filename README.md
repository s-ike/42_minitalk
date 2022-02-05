# 42_minitalk
サーバーとクライアントを作成し、クライアントは文字列を送信し、サーバーはそれを表示する.

プログラム間の通信はUNIXシグナルを使用して行う.

## Usage
`make` してから
`./server`とするとPIDが表示される.

別のターミナルから`./client 先ほどのPID "hello"`

長い文字列のテスト
``./client PID `python3 -c "print('a'*100)"` ``
