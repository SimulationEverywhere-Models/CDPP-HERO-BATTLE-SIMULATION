[Top]
components : Hero EnemyHero Creep EnemyCreep 
out : resultOut 
in : in 
Link : heroOut@Hero heroIn@EnemyHero
Link : creepOut@Hero heroIn@EnemyCreep
Link : heroOut@EnemyHero heroIn@Hero
Link : creepOut@EnemyHero heroIn@Creep
Link : heroOut@Creep creepIn@EnemyHero
Link : creepOut@Creep creepIn@EnemyCreep
Link : heroOut@EnemyCreep creepIn@Hero
Link : creepOut@EnemyCreep creepIn@Creep
Link : in creepIn@Hero
Link : resultOut@Hero resultOut

[Hero]
components : HDecision@HDecision HAttack@HAttack 
out : creepOut heroOut resultOut 
in : heroIn creepIn 
Link : attackOut@HDecision in@HAttack
Link : creepOut@HAttack creepOut
Link : heroOut@HAttack heroOut
Link : resultOut@HAttack resultOut
Link : heroIn heroIn@HDecision
Link : creepIn creepIn@HDecision

[HDecision]

[HAttack]


[EnemyHero]
components : EHDecision@HDecision EHAttack@HAttack 
out : creepOut heroOut resultOut 
in : heroIn creepIn 
Link : attackOut@EHDecision in@EHAttack
Link : creepOut@EHAttack creepOut
Link : heroOut@EHAttack heroOut
Link : resultOut@EHAttack resultOut
Link : heroIn heroIn@EHDecision
Link : creepIn creepIn@EHDecision

[HDecision]

[HAttack]

[Creep]
components : Creep1@CreepModel
out : creepOut heroOut 
in : creepIn heroIn 
Link : heroOut@Creep1 heroOut
Link : creepOut@Creep1 creepOut
Link : creepIn creepIn@Creep1
Link : heroIn heroIn@Creep1

[CreepModel]



[EnemyCreep]
components : Creep2@CreepModel 
out : creepOut heroOut 
in : creepIn heroIn 
Link : heroOut@Creep2 heroOut
Link : creepOut@Creep2 creepOut
Link : creepIn creepIn@Creep2
Link : heroIn heroIn@Creep2

[CreepModel]

