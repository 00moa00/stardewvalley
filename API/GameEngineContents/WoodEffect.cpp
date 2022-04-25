#include "WoodEffect.h"

WoodEffect::WoodEffect() 
{
}

WoodEffect::~WoodEffect() 
{
}

void WoodEffect::Start()
{
	Particles_[0] = GetLevel()->CreateActor<Particles>(static_cast<int>(PLAYLEVEL::TOP_OBJECT));
	Particles_[1] = GetLevel()->CreateActor<Particles>(static_cast<int>(PLAYLEVEL::TOP_OBJECT));
	Particles_[2] = GetLevel()->CreateActor<Particles>(static_cast<int>(PLAYLEVEL::TOP_OBJECT));
	Particles_[3] = GetLevel()->CreateActor<Particles>(static_cast<int>(PLAYLEVEL::TOP_OBJECT));
	Particles_[4] = GetLevel()->CreateActor<Particles>(static_cast<int>(PLAYLEVEL::TOP_OBJECT));
	Particles_[5] = GetLevel()->CreateActor<Particles>(static_cast<int>(PLAYLEVEL::TOP_OBJECT));
	Particles_[6] = GetLevel()->CreateActor<Particles>(static_cast<int>(PLAYLEVEL::TOP_OBJECT));
	Particles_[7] = GetLevel()->CreateActor<Particles>(static_cast<int>(PLAYLEVEL::TOP_OBJECT));


	Particles_[0]->SetMoveDir({ 150,-220 });
	Particles_[1]->SetMoveDir({ -150,-170 });
	Particles_[2]->SetMoveDir({ -120,-170 });
	Particles_[3]->SetMoveDir({ 100,-120 });
	Particles_[4]->SetMoveDir({ 70,-250 });
	Particles_[5]->SetMoveDir({ 50,-230 });
	Particles_[6]->SetMoveDir({ 170,-200 });
	Particles_[7]->SetMoveDir({ 150,-250 });


	Particles_[0]->GetRenderer()->SetImage("WoodParticle1.bmp");
	Particles_[1]->GetRenderer()->SetImage("WoodParticle2.bmp");
	Particles_[2]->GetRenderer()->SetImage("WoodParticle1.bmp");
	Particles_[3]->GetRenderer()->SetImage("WoodParticle1.bmp");
	Particles_[4]->GetRenderer()->SetImage("WoodParticle2.bmp");
	Particles_[5]->GetRenderer()->SetImage("WoodParticle2.bmp");
	Particles_[6]->GetRenderer()->SetImage("WoodParticle1.bmp");
	Particles_[7]->GetRenderer()->SetImage("WoodParticle2.bmp");

}

void WoodEffect::Update()
{
}

void WoodEffect::SetParticlesPosition(float4 _Position)
{
	SetPosition(_Position);
	Particles_[0]->SetPosition(_Position);
	Particles_[1]->SetPosition(_Position);
	Particles_[2]->SetPosition(_Position);
	Particles_[3]->SetPosition(_Position);
	Particles_[4]->SetPosition(_Position);
}
