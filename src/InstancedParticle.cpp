#include "InstancedParticle.h"

void InstancedParticle::setup()
{
    //shader loading
    {
        shader.load("of_shader");
    }

    //Mesh Load and Buffer Binding
    {
        ofBoxPrimitive boxPrimitive;
        ofSpherePrimitive sphere;
        ofConePrimitive cone;
        ofCylinderPrimitive cylinder;

        ofVboMesh mesh;

        cone.setResolution(10, 5, 5);
        sphere.setResolution(7);

        mesh = cone.getMesh();
        // mesh = sphere.getMesh();
        auto vertNum = mesh.getNumVertices();
        auto indexNum = mesh.getNumIndices();
        auto normNum = mesh.getNumNormals();

        amt = indexNum;

        cout << "mesh info\n"
            << "num verts: " << vertNum << "\n"
            << "num idx" << indexNum << "\n"
            << "num norm" << normNum << endl;

        ofVec3f* meshVertices;
        ofIndexType* meshIndeces;
        ofVec3f* meshNormals;

        meshVertices = new ofVec3f[vertNum];
        meshIndeces = new ofIndexType[indexNum];
        meshNormals = new ofVec3f[normNum];

        //load data
        {
            for (int i = 0; i < vertNum; i++)
            {
                meshVertices[i] = mesh.getVertex(i);
            }

            for (int i = 0; i < vertNum; i++)
            {
                meshIndeces[i] = mesh.getIndex(i);
            }

            for (int i = 0; i < vertNum; i++)
            {
                meshNormals[i] = mesh.getNormal(i);
            }

            //position setup
            float range = 10000;
            for (auto&& p : positions) {
                p = ofVec3f(ofRandom(-range, range), ofRandom(-range, range), ofRandom(-range, range));
            }

            //coloring setup
            for (auto&& c : colors) {
                float rand = ofRandom(1);

                if (rand < 0.3333)
                {
                    c = ofFloatColor(1.0, 0.5, 0.5, 1.0);

                }
                else if (rand < 0.6666)
                {
                    c = ofFloatColor(0.5, 1.0, 0.5, 1.0);
                }
                else
                {
                    c = ofFloatColor(0.5, 0.5, 1.0, 1.0);
                }

            }
        }


        bufferObject.allocate();
        bufferObject.bind(GL_ARRAY_BUFFER);
        bufferObject.setData(sizeof(ofVec3f) * OBJECT_NUM, &positions, GL_STATIC_DRAW);
        bufferObject.unbind(GL_ARRAY_BUFFER);

        vao.bind();

        vao.setVertexData(meshVertices, vertNum, GL_STATIC_DRAW);
        vao.setColorData(&colors[0], OBJECT_NUM, GL_STATIC_DRAW);
        vao.setAttributeBuffer(4, bufferObject, 3, 0, 0);
        vao.setIndexData(meshIndeces, indexNum, GL_STATIC_DRAW);
        vao.setNormalData(meshNormals, normNum, GL_STATIC_DRAW);


        //第一引数：GLSL内のLocationの番号のこと
        //第二引数：divisor に 1 を設定した場合、index で示される場所の頂点データは描画インスタンス毎にインクリメントされる
        vao.setAttributeDivisor(0, 0);
        vao.setAttributeDivisor(1, 1);
        vao.setAttributeDivisor(2, 0);
        vao.setAttributeDivisor(4, 1);
        vao.unbind();

    }

    //GUI Parameter Settings
    {
        lightColor.set("light color", ofFloatColor(1.0, 1.0, 1.0));
        ambientColor.set("ambient color", ofFloatColor(0.3, 0.3, 0.3));
        lightPosition.set("light position", ofVec3f(50, 50, 50), ofVec3f(-150, -150, -150), ofVec3f(150, 150, 150));
    }
}

void InstancedParticle::draw()
{
    float time = ofGetFrameNum() * 0.1;

    shader.begin();

    shader.setUniform1i("_ObjectNum", OBJECT_NUM);
    shader.setUniform1f("_Time", time);
    shader.setUniform3f("_Ambient", ambientColor->r, ambientColor->g, ambientColor->b);
    shader.setUniform3f("_LightColor0", lightColor->r, lightColor->g, lightColor->b);
    shader.setUniform3f("_LightPos", lightPosition->x, lightPosition->y, lightPosition->z);

    vao.drawElementsInstanced(GL_TRIANGLE_STRIP, amt, OBJECT_NUM);
    shader.end();
}

