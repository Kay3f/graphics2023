using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Attack", menuName = "Attack/Attack Data")]
public class AttackData_SO : ScriptableObject
{
    [Header("Player Base Data")]
    //������ֵ
    public int baseMinDamage;

    public int baseMaxDamage;

    public int baseSkillPower;

    public float baseCriticalChance;

    public float baseCriticalMagicChance;

    [Header("Physic")]
    //������������
    public float attackRange;
    //���⹥������
    public float skillRange;
    //������ȴʱ��(1/����)
    public float coolDown;

    //��ǰ��ֵ
    //�˺�����
    public int minDamage;

    public int maxDamage;
    //�����˺�
    public float criticalMultiplier;
    //������
    public float criticalChance;

    [Header("Magic")]
    //��ǿ
    public int SkillPower;
    //����������
    public float criticalMagicChance;
}
