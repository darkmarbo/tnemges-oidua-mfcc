#pragma once

#define STD_PCM_HEADER	1
#define BIG_PCM_HEADER	2
#define FACT_PCM_HEADER	3
#define NON_PCM_HEADER	4
#define EXT_PCM_HEADER	5

typedef   unsigned long   DWORD;
typedef   unsigned short   WORD;

typedef struct _WavHeadChunk_ {
	char riff[4];		//"RIFF"
	DWORD filelong;	//
	char waveid[4];		//"WAVE"
} WaveHeadChunk;

typedef struct _PCM_FormatChunk_ {
	char ckID[4];		//"fmt "
	DWORD ckSize;		//Chunk size: 16
	WORD wFormatTag;
	WORD nChannels;
	DWORD nSamplesPerSec;
	DWORD nAvgBytesPerSec;
	WORD  nBlockAlign;
	WORD  wBitsPerSample;
} PCM_FormatChunk;

typedef struct _NON_PCM_FormatChunk_ {
	char ckID[4];		//"fmt "
	DWORD ckSize;		//Chunk size: 16
	WORD wFormatTag;
	WORD nChannels;
	DWORD nSamplesPerSec;
	DWORD nAvgBytesPerSec;
	WORD  nBlockAlign;
	WORD  wBitsPerSample;
	WORD  cbSize;	
} NON_PCM_FormatChunk;

typedef struct _Ext_FormatChunk_ {
	char ckID[4];		//"fmt "
	DWORD ckSize;		//Chunk size: 16
	WORD wFormatTag;
	WORD nChannels;
	DWORD nSamplesPerSec;
	DWORD nAvgBytesPerSec;
	WORD  nBlockAlign;
	WORD  wBitsPerSample;
	WORD  cbSize;
	WORD  wValidBitsPerSample;
	DWORD dwChannelMask;
	char  SubFormat[16];
} Ext_FormatChunk;


typedef struct _FactChunk_ {
	char ckID[4];		//"fact"
	DWORD ckSize;		//chunk size : 4
	DWORD dwSampleLength;
} FactChunk;

typedef struct _DataChunk_ {
	char ckID[4];		//"data"
	DWORD ckSize;
} DataChunk;


// wave format definition
typedef struct _PCM_Data_ {
	WaveHeadChunk	wave_head_;
	PCM_FormatChunk format_chunk_;
	DataChunk	data_chunk_;
} PCM_Data;

typedef struct _Fact_PCM_Data_ {
	WaveHeadChunk	wave_head_;
	PCM_FormatChunk format_chunk_;
	FactChunk   fact_chunk_;
	DataChunk	data_chunk_;
} Fact_PCM_Data;

typedef struct _Big_PCM_Data_ {
	WaveHeadChunk	wave_head_;
	NON_PCM_FormatChunk format_chunk_;
	DataChunk	data_chunk_;
} Big_PCM_Data;

typedef struct _NON_PCM_Data_ {
	WaveHeadChunk	wave_head_;
	NON_PCM_FormatChunk format_chunk_;
	FactChunk   fact_chunk_;
	DataChunk	data_chunk_;
} NON_PCM_Data;

typedef struct _Ext_PCM_Data_ {
	WaveHeadChunk	wave_head_;
	Ext_FormatChunk format_chunk_;
	FactChunk   fact_chunk_;
	DataChunk	data_chunk_;
} Ext_PCM_Data;

class WaveIO
{
public:
	WaveIO(void);
	~WaveIO(void);

public:
	// ���ļ�����ȡͷ������
	CString openWave(CString pcsFileName);
	// ������Ƭ��д���ļ�
	CString writeWavFile(CString csOutFile, double fBegin, double fEnd);
	// WAVͷ�ļ���ʽ
	int m_nHeadType;
	// �����������ļ�����ȡ44�ֽڵı�׼WAV��ʽͷ
	PCM_Data getStdWavHeader(int nSamples=0);
	// ���ز�����
	int getSampleRate(void);
	// ����ͨ����
	int getChannels(void);
	// ���ز��������
	int getSamples(void);
	// ��ȡĳ��ͨ��ָ��ʱ��ε���������
	int getData(short** pData = NULL, int nChannel = 0, double fBeginStamp = 0, double fEndStamp = -1);

public:
	// ��׼��44�ֽ�Wavͷ
	PCM_Data m_pcm_header;
	// �Ǳ�׼46�ֽ�Wavͷ
	Big_PCM_Data m_big_header;
	// ��׼56�ֽ�FACT��ʽWavͷ
	Fact_PCM_Data m_fact_header;
	// ���ӵ�58�ֽڵ�NON_PCM��Wavͷ
	NON_PCM_Data m_non_header;
	// ��׼��EXT��ʽ��Wavͷ
	Ext_PCM_Data m_ext_header;
	// ��������
	short* m_pData;
};
