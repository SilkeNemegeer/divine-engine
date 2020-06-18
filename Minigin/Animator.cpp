#include "MiniginPCH.h"
#include "Animator.h"
#include "Debug.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "Time.h"
#include "GameObject.h"

divengine::Animator::Animator(const std::string& path, float clipHeight, float clipWidth)
	:m_Animations(std::map<unsigned int, AnimationClip*>())
	,m_AnimationSpeed{1.0f}
	,m_IsPlaying{false}
	,m_pCurrentAnimation(nullptr)
	,m_Path{path}
	,m_Cols{0}
	,m_Rows{0}
	,m_CurrentFrame{}
	,m_CurrentFrameTime{}
	,m_DestRect{}
	,m_SrcRect{}
	,m_pTransform{nullptr}
	, m_ClipHeight{ clipHeight }
	, m_ClipWidth{ clipWidth }
{
	m_TypeId = unsigned int(ComponentType::animator);

	m_SrcRect.w = int(clipWidth);
	m_SrcRect.h = int(clipHeight);
}

divengine::Animator::~Animator()
{
	for (auto pAnim : m_Animations)
	{
		SAFEDELETE(pAnim.second);
	}
}

void divengine::Animator::SetAnimation(AnimationClip* animation)
{
	//Set current clip
	m_pCurrentAnimation = animation;
}

void divengine::Animator::SetAnimation(unsigned int animId)
{

	if (m_Animations.find(animId) == m_Animations.end())
	{
		Debug::LogWarning("Animator::SetAnimation: invalid animation ID!");
		return;
	}

	SetAnimation(m_Animations[animId]);
}


void divengine::Animator::AddAnimation(AnimationClip *animation, unsigned int id)
{
	if (m_Animations.find(id) != m_Animations.end())
	{
		Debug::LogWarning("Animator::AddAnimation: an animation with this ID was already added!");
		return;
	}

	m_Animations[id] = animation;
	if (!m_pCurrentAnimation)
		m_pCurrentAnimation = animation;
}

void divengine::Animator::Load(divengine::BinaryReader& reader)
{
	reader.Read(m_IsPlaying);
	reader.Read(m_AnimationSpeed);
	reader.Read(m_CurrentFrame);
	reader.Read(m_CurrentFrameTime);
	reader.Read(m_SrcRect);
	reader.Read(m_DestRect);
	reader.Read(m_Cols);
	reader.Read(m_Rows);
	reader.Read(m_Path);
	reader.Read(m_ClipHeight);
	reader.Read(m_ClipWidth);
}

void divengine::Animator::Save(divengine::BinaryWriter& writer)
{
	writer.Write(m_IsPlaying);
	writer.Write(m_AnimationSpeed);
	writer.Write(m_CurrentFrame);
	writer.Write(m_CurrentFrameTime);
	writer.Write(m_SrcRect);
	writer.Write(m_DestRect);
	writer.Write(m_Cols);
	writer.Write(m_Rows);
	writer.Write(m_Path);
	writer.Write(m_ClipHeight);
	writer.Write(m_ClipWidth);
}

void divengine::Animator::Update()
{
	//Update current clip
	if (!m_IsPlaying || !m_pCurrentAnimation)
		return;
	
	//Update frame
	m_CurrentFrameTime += Time::GetInstance().GetDeltaTime() * m_AnimationSpeed;
	if (m_CurrentFrameTime >= (1.f / m_pCurrentAnimation->m_FramesPerSecond))
	{
		++m_CurrentFrame;
		m_CurrentFrameTime = 0.f;
	}
	m_CurrentFrame %= m_pCurrentAnimation->m_NrOfFrames;

	//index = (row * cols) + col
	int col = ( m_CurrentFrame + m_pCurrentAnimation->m_StartCol) % (m_Cols);
	int row = (m_pCurrentAnimation->m_StartRow + (( m_CurrentFrame + m_pCurrentAnimation->m_StartCol - col) / (m_Cols))) % m_Rows;

	m_SrcRect.x =  int((m_ClipWidth) * col);
	m_SrcRect.y = (int(m_ClipHeight) * row); 

	//Update dest rect
	auto pos = m_pTransform->GetPosition();
	m_DestRect.x = (int)pos.x;
	m_DestRect.y = (int)pos.y;
	
	m_pRenderComp->SetSourceRect(m_SrcRect);
	m_pRenderComp->SetDestRect(m_DestRect);
}

void divengine::Animator::Initialize()
{

}

void divengine::Animator::PostInitialize()
{

}

void divengine::Animator::Render()
{

}

void divengine::Animator::Start()
{
	m_pRenderComp = m_pGameObject->GetComponent<RenderComponent>();
	if (!m_pRenderComp)
	{
		m_pRenderComp = new RenderComponent(m_Path);
		m_pGameObject->AddComponent(m_pRenderComp);
	}

	m_pGameObject->AddComponent(m_pRenderComp);

	m_pTransform = m_pGameObject->GetComponent<TransformComponent>();
	if (!m_pTransform)
	{
		m_pTransform = new TransformComponent(Vector3());
		m_pGameObject->AddComponent(m_pTransform);
		Debug::LogWarning("Animator::Initialize: no transform component found");
	}

	m_pRenderComp->SetSourceRect(m_SrcRect);

	auto dimensions = m_pRenderComp->GetTextureDimensions();
	m_Cols = int(dimensions.x / m_ClipWidth);
	m_Rows = int(dimensions.y / m_ClipHeight);

	m_DestRect.x = (int)m_pTransform->GetPosition().x;
	m_DestRect.y = (int)m_pTransform->GetPosition().y;

	m_DestRect.w = int(m_SrcRect.w * m_pTransform->GetScale());
	m_DestRect.h = int(m_SrcRect.h * m_pTransform->GetScale());
	m_pRenderComp->SetDestRect(m_DestRect);
}

void divengine::Animator::Restart()
{
	//Reset current clip
	m_IsPlaying = true;
	m_AnimationSpeed = 1.0f;
	m_CurrentFrameTime = 0;
	m_CurrentFrame = 0;
	//Restart current clip
}

void divengine::Animator::Play()
{
	//Play/start current clip
	m_IsPlaying = true;
}

void divengine::Animator::Pause()
{
	m_IsPlaying = false;
}
