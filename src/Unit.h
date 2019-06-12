
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <cstring>

#include <alib.hpp>

#include "Common.h"
#include "Player.h"

namespace C35
{
struct Player;
struct Unit;

using alib::Refl;

class Capabilities
{
public:
	virtual bool CanMove() { return false; }
	virtual bool CanAttack() { return false; }
	virtual bool CanDefend() { return false; }
	virtual bool CaptureOnLoss() { return false; }
	virtual bool CanBombard() { return false; }
	virtual bool CanAirdrop() { return false; }
	virtual bool CanDefendBombard() { return false; }
	virtual bool CanBuild() { return false; }
	virtual bool CanMoveCity() { return false; }
	virtual bool CanMoveLand() { return false; }
	virtual bool CanMoveWater() { return false; }
	virtual bool CanSettle() { return false; }
	virtual bool CanJoin() { return false; }
	virtual bool CanColony() { return false; }
	virtual bool CanFortify() { return false; }

	virtual Capabilities* Clone() { return new Capabilities(); }

	static Capabilities& Default()
	{
		static Capabilities def;
		return def;
	}

	virtual ~Capabilities() = default;
};

class BasicTroop : public Capabilities
{
public:
	virtual bool CanMove() { return true; }
	virtual bool CanAttack() { return true; }
	virtual bool CanDefend() { return true; }
	virtual bool CanMoveCity() { return true; }
	virtual bool CanMoveLand() { return true; }
	virtual bool CanFortify() { return true; }

	virtual Capabilities* Clone() override { return new BasicTroop(); }
};

class VarCapa : public Capabilities
{
public:
	virtual bool CanMove() { return canMove; }
	virtual bool CanAttack() { return canAttack; }
	virtual bool CanDefend() { return canDefend; }
	virtual bool CaptureOnLoss() { return captureOnLoss; }
	virtual bool CanBombard() { return canBombard; }
	virtual bool CanAirdrop() { return canAirdrop; }
	virtual bool CanDefendBombard() { return canDefendBombard; }
	virtual bool CanBuild() { return canBuild; }
	virtual bool CanMoveCity() { return canMoveCity; }
	virtual bool CanMoveLand() { return canMoveLand; }
	virtual bool CanMoveWater() { return canMoveWater; }
	virtual bool CanSettle() { return canSettle; }
	virtual bool CanJoin() { return canJoin; }
	virtual bool CanColony() { return canColony; }
	virtual bool CanFortify() { return canFortify; }

	virtual Capabilities* Clone() { return new VarCapa(*this); }

protected:
	bool canMove, canAttack, canDefend, captureOnLoss, canBombard, canAirdrop;
	bool canDefendBombard, canBuild, canMoveCity, canMoveLand, canMoveWater;
	bool canSettle, canJoin, canColony, canFortify;
};

struct Capa
{
	bool pillage : 1;
	bool bombard : 1;
	bool airdrop : 1;
	bool def_bomb : 1;
	bool worker : 1;
	bool settle : 1;
	void Clear() { std::memset(this, 0, sizeof(Capa)); }
	Capa() : pillage(false), bombard(false), airdrop(false), def_bomb(false), worker(false), settle(false) {}
	Capa(bool p, bool b, bool a, bool d, bool w, bool s)
		: pillage(p), bombard(b), airdrop(a), def_bomb(d), worker(w), settle(s)
	{}
};

struct Stats
{
	int  xp, lev;
	int  hp, maxhp;
	int  off, def;
	int  move, maxmove;
	int  bombard_str;
	int  bombard_range;
	Capa oneoffs;
};

struct Movement
{
	bool land;
	bool sea;
	int  movement;
	int  remaining;
};

void UnitCreator();

struct UnitType
{
	int id;
	enum EBaseType
	{
		Off,
		Def,
		Bmb,
		Trn,
		None
	} basetype;
	enum EKind
	{
		Foot,
		Mounted,
		Vehicle,
		Sea,
		Air
	} kind;
	enum EPerk
	{
		NoPerk,
		OpenTerrainCombat,
		MountedDefense,
		MeleeCombat,
		FortifiedDefense,
		CityAssault,
		CityDefense,
		HigherGround,
		VehicleDefense
	} perk;
	int         start_off, start_def, start_bmb;
	int         range, move;
	int         join_num;
	int         load_capa;
	std::string name;
	Capa        capa;
	int         cost;
	int         res;
	bool        available;
	int         icon_id;

	void      LoadBmp(std::string);
	void      LoadAD(std::string);
	void      LoadAC(std::string);
	void      LoadLate(std::string);
	Refl      GetRefl(std::string, short, Player*);
	Refl      GetIcon(UC);
	Refl      GetIcon(Player* p) { return GetIcon(p->color); }
	alib::BA& GetIcon();
	void      Instance(Player*);
	void      DoneImg();
	//void      MakeWhite();
	//void      Scale150();

	static UnitType& New();
	static UnitType& Lookup(int);
	static int       Size();
	static void      Clear();

	static IdList ByName(std::string);
	static int    ToId(std::string);

	static void DoneAll();
	static void HaveAllNow();

	static Unit* MakeNewFromType(int, Player*);
	static Unit* MakeConscriptFromType(int, Player*);

private:
	UnitType() {}
	// UnitType(const UnitType& ut) { }
	static int                   nextId;
	static std::vector<UnitType> types;
	static alib::AD              unit_icons;

	// AnimCollection ac;
	// AnimDir        ad;
	// CIS            cis;
	enum
	{
		have_name,
		have_ac,
		have_ad,
		have_cis,
		have_none
	} have_gfx;
	std::string gfxname;

	friend void UnitCreator();

	friend struct Unit;
};

enum class UnitId
{
	none,
	worker,
	settler,
	warrior,
	curragh,
	horseman,
	pikeman,
	galley,
	fregatte,
	barbarian,
	max
};
extern UnitType* worker_utp;
extern UnitType* settler_utp;
extern UnitType* warrior_utp;
extern UnitType* curragh_utp;
extern UnitType* horseman_utp;
extern UnitType* pikeman_utp;
extern UnitType* galley_utp;
extern UnitType* fregatte_utp;
extern UnitType* barbarian_utp;

struct Unit
{
	int id;
	int type;

	Stats stats;

	Orders* orders;

	Player* owner;

	bool currently;

	void ClearForTurn();
	void Won();

	static int   NewID();
	static void  Register(int, Unit*);
	static Unit* Lookup(int);
	static void  ClearAll();

	Capabilities& Capa();

	// static Unit* MakeNewFromType(int,Player*);

	bool WantsOrder();
	bool AcceptsOrder();
	void ExecuteOrder(Board*);
	void AbortOrder();

	bool CanLoad(const Unit*) const;
	void DoLoad(Unit*);
	bool CanUnload(int, int) const;
	bool CanUnload(Dir6) const;
	void DoUnload(int, int);
	void DoUnload(Dir6);

	bool CanGo(Dir6) const;
	void DoGo(Dir6);

	Movement MakeMovement();

	bool CanCity();

	void KillUnit();

	void Attack(Dir6);

	void Display(int, int);
	void SetAnim(std::string, int);
	void Update(int);
	Refl GetIcon();

	int x, y;

	bool visible;

	static Unit* FromStream(std::istream&, Player*);
	void         ToStream(std::ostream&);

	std::vector<Unit*> loaded;
	std::vector<UC>    perks;

	friend struct UnitType;

private:
	void                      OrderDone(bool = false);
	void                      AutoPilot();
	static int                nextId;
	static std::vector<Unit*> units;
	VarCapa                   capa;
	char                      buffer[256];
	Refl                      ar;
};

}  // namespace C35
