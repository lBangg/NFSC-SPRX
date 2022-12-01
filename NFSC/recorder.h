#include "sysutil/sysutil_rec.h"
sys_memory_container_t recContainer;
bool isRecON = false;

void RecordingClose()
{
	/* Save file and terminate the recording utility */
	if (cellRecClose(0) < 0) {
		_sys_printf("cellRecClose error\n");
	}
}

void recCallback(int recStatus, int recError, void* p)
{
	if (recStatus == CELL_REC_STATUS_OPEN)
	{
		_sys_printf("CELL_REC_STATUS_OPEN\n");
	}
	if (recStatus == CELL_REC_STATUS_ERR)
	{
		_sys_printf("CELL_REC_STATUS_ERR\n");
	}
	if (recStatus == CELL_REC_STATUS_STOP)
	{
		_sys_printf("CELL_REC_STATUS_STOP\n");

		RecordingClose();
	}
	if (recStatus == CELL_REC_STATUS_START)
	{
		_sys_printf("CELL_REC_STATUS_START\n");
	}
	if (recStatus == CELL_REC_STATUS_CLOSE)
	{
		_sys_printf("CELL_REC_STATUS_CLOSE\n");
		if (recContainer != SYS_MEMORY_CONTAINER_ID_INVALID) {
			sys_memory_container_destroy(recContainer);
		}
	}
}

void RecordInit()
{
	int ret = cellSysmoduleLoadModule(CELL_SYSMODULE_SYSUTIL_REC);
	if (ret < 0) {
		_sys_printf("cellSysmoduleLoadModule error\n");
		return;
	}

	CellRecParam recParam;
	recParam.videoFmt = CELL_REC_PARAM_VIDEO_FMT_M4HD_HD720_2048K_30FPS;
	recParam.audioFmt = CELL_REC_PARAM_AUDIO_FMT_AAC_64K;
	recParam.numOfOpt = 0; /* No options */
	recParam.pOpt = NULL;
	size_t memSize = cellRecQueryMemSize(&recParam);
	ret = sys_memory_container_create(&recContainer, memSize);
	if (ret < 0) {
		_sys_printf("sys_memory_container_create error\n");
		return;
	}
	char buffer[32];
	_sys_sprintf(buffer,"NFSC_%lld.mp4", time(NULL));
	ret = cellRecOpen("/dev_hdd0/video", buffer, &recParam, recContainer, recCallback, NULL);
	if (ret < 0)
	{
		_sys_printf("cellRecOpen error\n");
		return;
	}
}


