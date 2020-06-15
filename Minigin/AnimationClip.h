#pragma once
#include <string>
namespace divengine
{
	struct AnimationClip //has settings for a certain animation
	{
		public:
			AnimationClip(int startColumn, int startRow , int nrOfFrames, const std::string& name, int framesPerSec = 5)
				:m_NrOfFrames{nrOfFrames} 
				,m_Name{name}
			//	,m_StartClipPos{startClipPos}
				,m_StartCol{startColumn}
				,m_StartRow{startRow}
				

				,m_FramesPerSecond{framesPerSec}
			{};
		
		int m_NrOfFrames;
		//glm::vec2 m_StartClipPos;
		int m_FramesPerSecond;
		std::string m_Name;
		int m_StartCol, m_StartRow;
	};
}
