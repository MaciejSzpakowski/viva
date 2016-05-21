cbuffer cbBufferPS
{
    float4 color;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 Col : COLOR;
    float2 TexCoord : TEXCOORD;
};

float4 main(VS_OUTPUT input) : SV_TARGET
{
    float4 result = ObjTexture.Sample(ObjSamplerState, input.TexCoord);
    clip(result.a - 0.001f);
    return result * color;
}