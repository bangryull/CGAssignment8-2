202111302 백진률 Computer Graphics Assignment 8 – Q2

구현 세부 사항
1.1 main.cpp
GLUT를 이용하여 OpenGL 창을 생성하고, 콜백 함수 등록 및 load_mesh() 호출을 통해 모델을 불러옵니다. 프로그램의 진입점으로 전체 파이프라인을 초기화하며, 렌더링 루프(glutMainLoop)를 시작합니다.

1.2 load_mesh.cpp
Stanford Bunny 모델이 저장된 .obj 파일을 파싱하여 정점 좌표(gPositions), 법선 벡터(gNormals), 삼각형 인덱스(gTriangles)를 메모리에 저장합니다.
각 f(face) 요소는 인덱스를 통해 정점과 법선을 참조하며, 중복 없이 저장됩니다.

1.3 frame_timer.cpp
glGenQueries, glBeginQuery, glEndQuery, glGetQueryObjectiv 등을 통해 GPU 렌더링 시간(GL_TIME_ELAPSED)을 측정하고, 이를 기반으로 FPS를 계산해 화면에 표시하는 역할을 합니다.
display() (main.cpp 내 렌더링 콜백 함수)
매 프레임마다 모델을 Vertex Array Object (VAO) + Vertex Buffer Object (VBO)를 이용해 렌더링합니다.
정점 좌표와 법선 벡터를 각각의 VBO로 업로드한 후 glDrawArrays(GL_TRIANGLES)를 호출하여 그립니다.
고정 기능 파이프라인의 Phong 조명 모델(ambient + diffuse)을 이용합니다.

2 결과 화면
![image](https://github.com/user-attachments/assets/60a9d61e-8331-4c2f-b4c7-2237b150f732)
Average FPS: 6850

3.1 필요 라이브러리
GLEW: OpenGL 확장 기능
GLUT: 창 및 입력 이벤트 처리
OpenGL / GLU: 기본 렌더링 API

3.2 컴파일 및 실행 방법
Visual Studio에서 솔루션 파일을 엽니다.
필요한 라이브러리(GLEW, GLUT, OpenGL, GLU)가 포함되어 있는지 확인합니다.
프로젝트를 빌드하고 실행합니다.
