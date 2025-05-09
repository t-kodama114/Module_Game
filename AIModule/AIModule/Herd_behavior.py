import ctypes

# DLL�̃��[�h
mydll = ctypes.CDLL('./Herd_behavior.dll') 

# �֐��̒�`
optimizePositions = mydll.addSS
optimizePositions.argtypes = [ctypes.c_int, ctypes.c_int]
optimizePositions.restype = ctypes.c_int

hello = mydll.hello
hello.argtypes = []
hello.restype = None

# �֐��̌Ăяo��
'add�̊֐����Ăяo���A�����Ƃ��ĂR�E�T��n��'
'�߂�l��result�ϐ��Ɋi�[���Č��ʂ��o��'
result = optimizePositions(3, 5)
print(f"Result of add(3, 5): {result}")

'hello�֐����Ăяo���A�����Ȃ�'
hello()


import win32pipe
import win32file
import json
import time

PIPE_NAME = r'\\.\pipe\SwarmPipe'

def send_data(data):
    """NamedPipe���쐬���AUnity�փf�[�^�𑗐M"""
    pipe = win32pipe.CreateNamedPipe(
        PIPE_NAME,
        win32pipe.PIPE_ACCESS_OUTBOUND,
        win32pipe.PIPE_TYPE_MESSAGE | win32pipe.PIPE_WAIT,
        1, 65536, 65536, 0, None
    )

    print("Waiting for Unity to connect...")
    win32pipe.ConnectNamedPipe(pipe, None)  # Unity�����ڑ�����܂őҋ@
    print("Connected! Sending data...")

    # JSON�f�[�^�𑗐M
    win32file.WriteFile(pipe, json.dumps(data).encode('utf-8'))
    win32file.CloseHandle(pipe)

if __name__ == "__main__":
    while True:
        # ���̈ʒu�f�[�^���쐬�i�G10�́j
        positions = [{"x": i * 1.5, "y": i * 2.0} for i in range(10)]
        
        # NamedPipe��Unity�ɑ��M
        send_data(positions)

        # 1�b�Ԋu�ő��M
        time.sleep(1)
