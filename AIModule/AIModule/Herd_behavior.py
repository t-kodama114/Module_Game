import ctypes

# DLLのロード
mydll = ctypes.CDLL('./Herd_behavior.dll') 

# 関数の定義
optimizePositions = mydll.addSS
optimizePositions.argtypes = [ctypes.c_int, ctypes.c_int]
optimizePositions.restype = ctypes.c_int

hello = mydll.hello
hello.argtypes = []
hello.restype = None

# 関数の呼び出し
'addの関数を呼び出し、引数として３・５を渡す'
'戻り値をresult変数に格納して結果を出力'
result = optimizePositions(3, 5)
print(f"Result of add(3, 5): {result}")

'hello関数を呼び出し、引数なし'
hello()


import win32pipe
import win32file
import json
import time

PIPE_NAME = r'\\.\pipe\SwarmPipe'

def send_data(data):
    """NamedPipeを作成し、Unityへデータを送信"""
    pipe = win32pipe.CreateNamedPipe(
        PIPE_NAME,
        win32pipe.PIPE_ACCESS_OUTBOUND,
        win32pipe.PIPE_TYPE_MESSAGE | win32pipe.PIPE_WAIT,
        1, 65536, 65536, 0, None
    )

    print("Waiting for Unity to connect...")
    win32pipe.ConnectNamedPipe(pipe, None)  # Unity側が接続するまで待機
    print("Connected! Sending data...")

    # JSONデータを送信
    win32file.WriteFile(pipe, json.dumps(data).encode('utf-8'))
    win32file.CloseHandle(pipe)

if __name__ == "__main__":
    while True:
        # 仮の位置データを作成（敵10体）
        positions = [{"x": i * 1.5, "y": i * 2.0} for i in range(10)]
        
        # NamedPipeでUnityに送信
        send_data(positions)

        # 1秒間隔で送信
        time.sleep(1)
