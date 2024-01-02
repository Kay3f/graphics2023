using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public enum AttackType
{
    NEAR,
    MAGICBUllET,
    DEFENCE
}

public class PlayerController : MonoBehaviour
{
    private NavMeshAgent agent;

    private Animator anim;

    private CharacterStats characterStats;

    public GameObject attackTarget;

    public int playerID;
    public GameObject myBag;
    public GameObject playerAllInfor;
    public GameObject inventoryManagerGO;
    public InventoryManager inventoryManager;
    public Inventory myBagData;
    public SkillManager skillManager;
    private SkillSlot skillSlot;
    public Vector3 skillTargetPo;
    public AttackType attackType;
    public GameObject Bullet;
    public Transform BulletStartPo;

    private float lastOneSecond;

    //�����ʾ
    public Transform dataTransform;

    //�������

    private float lastAttackTime;

    private bool isDead;

    public float stopDistance;

    public float hitForce = 20;
    public GameObject buffPanel;

    private void Awake()
    {
        //DontDestroyOnLoad(gameObject);
        agent = GetComponent<NavMeshAgent>();
        anim = GetComponent<Animator>();
        characterStats = GetComponent<CharacterStats>();
        inventoryManager = inventoryManagerGO.GetComponent<InventoryManager>();

        stopDistance = agent.stoppingDistance;
        
        checkBagOpen();
    }

    private void Start()
    {
        startFun();
        GameManager.Instance.RigisterPlayer(characterStats, playerID);
    }

    public void startFun()
    {
        MouseManger.Instance.OnMouseClicked += MoveToTarget;
        MouseManger.Instance.OnEnemyClicked += EventAttack;
        MouseManger.Instance.OnItemClicked += EventPick;

    }

    private void Update()
    {
        isDead = characterStats.currentHealth == 0;
        if (isDead)
        {
            GameManager.Instance.NotifyObservers();
        }
        
        SwitchAnimation();

        lastAttackTime -= Time.deltaTime;
        UpdatePlayerStats();

        OpenMyBag();
        UpdatePlayerDataUI();
    }

    private void SwitchAnimation()
    {
        anim.SetFloat("Speed", agent.velocity.sqrMagnitude);
        anim.SetBool("Death", isDead);
    }

    public void MoveToTarget(Vector3 target)
    {
        StopAllCoroutines();
        if (isDead)
        {
            return;
        }

        agent.stoppingDistance = stopDistance;
        agent.isStopped = false;
        agent.destination = target;
        attackTarget = null;
        
    }

    public void EventAttack(GameObject target)
    {
        if (isDead)
        {
            return;
        }
        if (target != null)
        {
            attackTarget = target;

            characterStats.isCritical = UnityEngine.Random.value < characterStats.attackData.criticalChance;

            StartCoroutine(MoveToAttackTarget());

        }
    }

    IEnumerator MoveToAttackTarget()
    {
        do
        {
            if (attackTarget.GetComponent<CharacterStats>() && attackTarget.GetComponent<CharacterStats>().currentHealth <= 0)
            {
                break;
            }
            agent.isStopped = false;
            agent.stoppingDistance = characterStats.attackData.attackRange;

            //ת��
            transform.LookAt(attackTarget.transform);

            //�߹�ȥ
            while (attackTarget != null & Vector3.Distance(attackTarget.transform.position, transform.position) > characterStats.attackData.attackRange)
            {
                agent.destination = attackTarget.transform.position;
                yield return null;
            }

            try
            {
                agent.isStopped = true;
                //����
                if (lastAttackTime < 0)
                {
                    //if(characterStats.isCritical)
                    //    Debug.Log("����");
                    anim.SetBool("Critical", characterStats.isCritical);
                    anim.SetTrigger("Attack");
                    switch (attackType)
                    {
                        case AttackType.MAGICBUllET:
                            GameObject BulletGO = Instantiate(Bullet, BulletStartPo.position, gameObject.transform.rotation);
                            BulletGO.GetComponent<MagicBullet>().Target = attackTarget;
                            BulletGO.GetComponent<MagicBullet>().attackerCharacterStats = characterStats;

                            break;
                    }
                    //���ù���
                    lastAttackTime = characterStats.attackData.coolDown;
                }
                agent.isStopped = false;
            }
            catch(Exception e)
            {
                Debug.Log(e);
            }
            yield return null;
        }
        while (attackTarget != null && Vector3.Distance(transform.position, attackTarget.transform.position) <= 1.5 * characterStats.attackData.attackRange);
        

        attackTarget = null;
        agent.isStopped = false;
    }


    //Animation Event
    void Hit()
    {
        if (attackTarget != null)
        {
            if (attackTarget.CompareTag("Attackable"))
            {
                if (attackTarget.GetComponent<Rock>() && attackTarget.GetComponent<Rock>().rockStates == Rock.RockStates.HitNothing)
                {

                    attackTarget.GetComponent<Rock>().rockStates = Rock.RockStates.HitEnemy;
                    attackTarget.GetComponent<Rigidbody>().velocity = Vector3.one;
                    attackTarget.GetComponent<Rigidbody>().AddForce(transform.forward * hitForce, ForceMode.Impulse);
                }
            }
            else if (attackTarget.CompareTag("Enemy"))
            {
                var targetStats = attackTarget.GetComponent<CharacterStats>();

                targetStats.TakeDamage(characterStats, targetStats);
            }
        }
        
        
    }

    void OpenMyBag()
    {
        if (Input.GetKeyDown(KeyCode.I))
        {
            //isOpen = !isOpen;
            playerAllInfor.SetActive(!playerAllInfor.activeSelf);
            checkBagOpen();
        }
    }

    private void EventPick(GameObject target)
    {
        StopAllCoroutines();

        if (isDead)
        {
            return;
        }

        if (target != null)
        {
            attackTarget = target;

            StartCoroutine(MoveToPickTarget());
        }
        else
        {
            attackTarget = null;
        }
        //agent.stoppingDistance = 4;
        //agent.isStopped = false;
        //agent.destination = target.transform.position;

    }

    IEnumerator MoveToPickTarget()
    {
        agent.isStopped = false;
        agent.stoppingDistance = 4;
        //ת��
        transform.LookAt(attackTarget.transform);

        //�߹�ȥ
        while (Vector3.Distance(attackTarget.transform.position, transform.position) > agent.stoppingDistance)
        {
            agent.destination = attackTarget.transform.position;
            yield return null;

        }

        agent.isStopped = true;
        //Debug.Log(attackTarget);
        //ʰȡ
        if (attackTarget.GetComponent<ItemOnWorld>())
        {
            attackTarget.GetComponent<ItemOnWorld>().AddNewItem(inventoryManager, myBagData);
        }

        agent.stoppingDistance = stopDistance;
        agent.isStopped = false;
    }

    public void checkBagOpen()
    {
        if (playerAllInfor.activeSelf)
        {
            //agent.enabled = false;
        }
        else
        {
            inventoryManager.RefreshInventory();
            inventoryManager.initAllEquipSlots();
            //agent.enabled = true;
        }
    }

    void UpdatePlayerDataUI()
    {
        if (dataTransform.gameObject.activeSelf)
        {
            dataTransform.GetChild(0).GetChild(1).gameObject.GetComponent<Text>().text = 
                characterStats.currentHealth.ToString() + "/" + characterStats.maxHealth.ToString();
            dataTransform.GetChild(1).GetChild(1).gameObject.GetComponent<Text>().text =
                characterStats.currentMana.ToString() + "/" + characterStats.maxMana.ToString();
            dataTransform.GetChild(2).GetChild(1).gameObject.GetComponent<Text>().text =
                characterStats.characterData.currentExp.ToString() + "/" + characterStats.characterData.baseExp.ToString();
            dataTransform.GetChild(3).GetChild(1).gameObject.GetComponent<Text>().text =
                characterStats.currentDefence.ToString();
            dataTransform.GetChild(4).GetChild(1).gameObject.GetComponent<Text>().text =
                characterStats.currentMagicDefence.ToString();
            dataTransform.GetChild(5).GetChild(1).gameObject.GetComponent<Text>().text =
                characterStats.attackData.minDamage.ToString() + "/" + characterStats.attackData.maxDamage.ToString();
            dataTransform.GetChild(6).GetChild(1).gameObject.GetComponent<Text>().text =
                characterStats.attackData.SkillPower.ToString();
            dataTransform.GetChild(7).GetChild(1).gameObject.GetComponent<Text>().text =
                characterStats.attackData.criticalChance.ToString();
            dataTransform.GetChild(8).GetChild(1).gameObject.GetComponent<Text>().text =
                characterStats.attackData.criticalMagicChance.ToString();
        }
    }

    void UpdatePlayerStats()
    {
        if (!isDead)
        {
            float dt = Time.time - lastOneSecond;
            //Debug.Log(characterStats.currentMana);
            if (dt >= 1.0f)
            {
                lastOneSecond = Time.time;
                characterStats.currentHealth += Convert.ToInt16(dt * characterStats.currentHealthRecover);
                //Debug.Log(Convert.ToInt16(dt * characterStats.currentHealthRecover));
                characterStats.currentMana += Convert.ToInt16(dt * characterStats.currentManaRecover);
            }
            if (characterStats.currentHealth > characterStats.maxHealth)
            {
                characterStats.currentHealth = characterStats.maxHealth;
            }
            if (characterStats.currentMana > characterStats.maxMana)
            {
                characterStats.currentMana = characterStats.maxMana;
            }
        }
        
    }

    public void ChooseSkillTarget(SkillSlot skillSlot)
    {
        this.skillSlot = skillSlot;
        StartCoroutine("ChooseSkillTargetPo");
    }

    IEnumerator ChooseSkillTargetPo()
    {
        while (true)
        {
            if (Input.GetMouseButtonDown(1))
            {
                break;
            }
            else if (Input.GetMouseButtonDown(0))
            {
                PointerEventData eventData = new PointerEventData(EventSystem.current);
                eventData.position = Input.mousePosition;
                List<RaycastResult> raycastResults = new List<RaycastResult>();
                //����λ�÷���һ�����ߣ�����Ƿ���UI
                EventSystem.current.RaycastAll(eventData, raycastResults);
                if (raycastResults.Count > 0)
                {
                    yield return null;
                    continue;
                }
                RaycastHit hitInfo;
                Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

                if (Physics.Raycast(ray, out hitInfo))
                {
                    skillTargetPo = hitInfo.point;
                    skillSlot.targetPo = hitInfo.point;
                    StartCoroutine("MoveToSkillTargetPo");
                    break;
                }
            }
            yield return null;
        }

    }

    IEnumerator MoveToSkillTargetPo()
    {
        agent.isStopped = false;
        agent.stoppingDistance = skillSlot.skillData.skillRange;

        //ת��
        transform.LookAt(skillTargetPo);

        //�߹�ȥ
        while (Vector3.Distance(skillTargetPo, transform.position) > skillSlot.skillData.skillRange)
        {
            agent.destination = skillTargetPo;
            yield return null;
        }

        agent.isStopped = true;

        //���ܶ�������
        skillSlot.doSkill();

        agent.isStopped = false;
    }

}
